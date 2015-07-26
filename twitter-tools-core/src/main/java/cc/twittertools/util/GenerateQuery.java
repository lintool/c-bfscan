package cc.twittertools.util;

import java.io.BufferedWriter;
import java.io.File;
import java.io.IOException;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.io.StringReader;
import java.util.List;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.GnuParser;
import org.apache.commons.cli.HelpFormatter;
import org.apache.commons.cli.OptionBuilder;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.ParseException;
import org.apache.log4j.Logger;
import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.TokenStream;
import org.apache.lucene.analysis.tokenattributes.CharTermAttribute;
import org.apache.lucene.util.Version;

import cc.twittertools.corpus.data.JsonStatusCorpusReader;
import cc.twittertools.corpus.data.Status;
import cc.twittertools.corpus.data.StatusStream;
import cc.twittertools.index.TweetAnalyzer;
import cc.twittertools.search.TrecTopic;
import cc.twittertools.search.TrecTopicSet;

import com.google.common.collect.Lists;

import edu.umd.cloud9.util.map.HMapII;
import edu.umd.cloud9.util.map.MapII;

public class GenerateQuery {
	private static final Logger LOG = Logger.getLogger(GenerateQuery.class);
	public static final Analyzer ANALYZER = new TweetAnalyzer(Version.LUCENE_43);

	private static final String INDEX_OPTION = "index";
	private static final String QUERY_OPTION = "query";
	private static final String OUTPUT_OPTION = "output";

	@SuppressWarnings("static-access")
	public static void main(String[] args) throws Exception {
		Options options = new Options();

		options.addOption(OptionBuilder.withArgName("path").hasArg()
				.withDescription("index location").create(INDEX_OPTION));
		options.addOption(OptionBuilder.withArgName("path").hasArg()
				.withDescription("collection location").create(QUERY_OPTION));
		options.addOption(OptionBuilder.withArgName("path").hasArg()
				.withDescription("output location").create(OUTPUT_OPTION));

		CommandLine cmdline = null;
		CommandLineParser parser = new GnuParser();
		try {
			cmdline = parser.parse(options, args);
		} catch (ParseException exp) {
			System.err.println("Error parsing command line: " + exp.getMessage());
			System.exit(-1);
		}

		if (!cmdline.hasOption(INDEX_OPTION) || !cmdline.hasOption(QUERY_OPTION) || !cmdline.hasOption(OUTPUT_OPTION)) {
			HelpFormatter formatter = new HelpFormatter();
			formatter.printHelp(GenerateQuery.class.getName(), options);
			System.exit(-1);
		}

		String indexPath = cmdline.getOptionValue(INDEX_OPTION);
		File indexLocation = new File(indexPath);
		if (!indexLocation.exists()) {
			System.err.println("Error: " + indexLocation + " does not exist!");
			System.exit(-1);
		}
		String queryPath = cmdline.getOptionValue(QUERY_OPTION);
		File queryLocation = new File(queryPath);
		if (!queryLocation.exists()) {
			System.err.println("Error: " + queryLocation + " does not exist!");
			System.exit(-1);
		}
		String outputPath = cmdline.getOptionValue(OUTPUT_OPTION);

		LOG.info("Reading term statistics.");
		TermStatistics termStats = new TermStatistics(indexPath);
		LOG.info("Finished reading term statistics.");

		BufferedWriter bw_query = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(outputPath)));

		TrecTopicSet topics = TrecTopicSet.fromFile(new File(queryPath));
		int c = 1;
		String topicStr = "int *topics[] = {\n";
		String timeStr = "long topics_time[] = {\n";
		for ( TrecTopic topic : topics ) {  
			List<String> queryterms = parse(ANALYZER, topic.getQuery());
			topicStr += "(int []) {" + c + ", " + queryterms.size() + ", ";
			timeStr += topic.getQueryTweetTime() + ",\n";
			int cnt = 0;
			for (String term : queryterms) {
				cnt ++;
				int id = termStats.getId(term);
				if (!termStats.getTerm2Id().containsKey(term)) {
					id = -1;
				}
				if (cnt < queryterms.size()) {
					topicStr += id + ", ";
				} else {
					topicStr += id;
				}
			}
			c ++;
			topicStr += "},\n";
		}
		topicStr += "};\n";
		timeStr += "};\n";
		bw_query.write(topicStr);
		bw_query.newLine();
		bw_query.write(timeStr);
		bw_query.newLine();
		bw_query.close();
	}

	public static List<String> parse(Analyzer analyzer, String s) throws IOException {
		List<String> list = Lists.newArrayList();

		TokenStream tokenStream = analyzer.tokenStream(null, new StringReader(s));
		CharTermAttribute cattr = tokenStream.addAttribute(CharTermAttribute.class);
		tokenStream.reset();
		while (tokenStream.incrementToken()) {
			list.add(cattr.toString());
		}
		tokenStream.end();
		tokenStream.close();

		return list;
	}
}
