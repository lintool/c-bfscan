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

import com.google.common.collect.Lists;

import edu.umd.cloud9.util.map.HMapII;
import edu.umd.cloud9.util.map.MapII;

public class GenerateStatistics {
	private static final Logger LOG = Logger.getLogger(GenerateStatistics.class);
	public static final Analyzer ANALYZER = new TweetAnalyzer(Version.LUCENE_43);

	private static final String INDEX_OPTION = "index";
	private static final String COLLECTION_OPTION = "collection";
	private static final String OUTPUT_OPTION = "output";

	@SuppressWarnings("static-access")
	public static void main(String[] args) throws Exception {
		Options options = new Options();

		options.addOption(OptionBuilder.withArgName("path").hasArg()
				.withDescription("index location").create(INDEX_OPTION));
		options.addOption(OptionBuilder.withArgName("path").hasArg()
				.withDescription("collection location").create(COLLECTION_OPTION));
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

		if (!cmdline.hasOption(INDEX_OPTION) || !cmdline.hasOption(COLLECTION_OPTION) || !cmdline.hasOption(OUTPUT_OPTION)) {
			HelpFormatter formatter = new HelpFormatter();
			formatter.printHelp(GenerateStatistics.class.getName(), options);
			System.exit(-1);
		}

		String indexPath = cmdline.getOptionValue(INDEX_OPTION);
		File indexLocation = new File(indexPath);
		if (!indexLocation.exists()) {
			System.err.println("Error: " + indexLocation + " does not exist!");
			System.exit(-1);
		}
		String collectionPath = cmdline.getOptionValue(COLLECTION_OPTION);
		File collectionLocation = new File(collectionPath);
		if (!collectionLocation.exists()) {
			System.err.println("Error: " + collectionLocation + " does not exist!");
			System.exit(-1);
		}
		String outputPath = cmdline.getOptionValue(OUTPUT_OPTION);

		LOG.info("Reading term statistics.");
		TermStatistics termStats = new TermStatistics(indexPath);
		LOG.info("Finished reading term statistics.");

		StatusStream stream = new JsonStatusCorpusReader(collectionLocation);

		if (!new File(outputPath).exists()) {
			new File(outputPath).mkdir();
		}

		BufferedWriter bw_id = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(outputPath + "/doc_id.txt")));
		BufferedWriter bw_length = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(outputPath + "/doc_length.txt")));
		BufferedWriter bw_term_ordered = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(outputPath + "/all_terms_ordered.txt")));
		BufferedWriter bw_tf = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(outputPath + "/all_terms_tf.txt")));
		BufferedWriter bw_length_ordered = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(outputPath + "/doc_length_ordered.txt"))); 
		BufferedWriter bw_cf = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(outputPath + "/cf_table.txt")));
		BufferedWriter bw_stats = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(outputPath + "/stats.txt")));

		for (int id = 0; id < termStats.getId2Term().size(); id ++) {
			bw_cf.write(String.valueOf(termStats.getFreq(id)));
			bw_cf.newLine();
		}
		bw_cf.close();

		int cnt = 0;
		int collection_unique_term_size = 0;
		int collection_all_term_size = 0;
		Status status;
		while ((status = stream.next()) != null) {
			if (status.getText() == null) {
				continue;
			}
			bw_id.write(String.valueOf(status.getId()));
			bw_id.newLine();

			List<String> terms = parse(ANALYZER, status.getText());
			bw_length.write(String.valueOf(terms.size()));
			bw_length.newLine();

			HMapII docVector = new HMapII();
			HMapII docTermFreq = new HMapII();
			for (String term : terms) {
				if (termStats.getTerm2Id().containsKey(term)) {
					int termId = termStats.getId(term);
					if (docVector.containsKey(termId)) {
						docTermFreq.put(termId, docTermFreq.get(termId) + 1);
					} else {
						docTermFreq.put(termId, 1);
						docVector.put(termId, termStats.getDf(termId));
					}
				}
			}
			bw_length_ordered.write(String.valueOf(docVector.size()));
			bw_length_ordered.newLine();
			collection_unique_term_size += docVector.size();
			collection_all_term_size += terms.size();

			if (docVector.size() > 0) {
				for (MapII.Entry entry : docVector.getEntriesSortedByValue()) {
					int key = entry.getKey();
					bw_term_ordered.write(String.valueOf(key));
					bw_term_ordered.newLine();
					bw_tf.write(String.valueOf(docTermFreq.get(key)));
					bw_tf.newLine();
				}	
			}

			cnt++;
			if (cnt % 100000 == 0) {
				LOG.info(cnt + " processed");
			}
		}
		LOG.info("Total " + cnt + " processed");

		stream.close();
		bw_id.close();
		bw_length.close();
		bw_term_ordered.close();
		bw_tf.close();
		bw_length_ordered.close();
		bw_stats.write(String.valueOf(cnt));
		bw_stats.newLine();
		bw_stats.write(collection_unique_term_size);
		bw_stats.newLine();
		bw_stats.write(collection_all_term_size);
		bw_stats.newLine();
		bw_stats.write(termStats.getId2Term().size());
		bw_stats.newLine();
		bw_stats.close();
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
