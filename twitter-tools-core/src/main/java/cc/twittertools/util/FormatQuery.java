package cc.twittertools.util;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileNotFoundException;
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

public class FormatQuery {
	private static final Logger LOG = Logger.getLogger(FormatQuery.class);
	public static final Analyzer ANALYZER = new TweetAnalyzer(Version.LUCENE_43);

	private static final String INPUT_OPTION = "input";
	private static final String TOP_OPTION = "top";
	private static final String OUTPUT_OPTION = "output";
	private static final String LAST_TWEET_TIME = "35125724180516864";

	@SuppressWarnings("static-access")
	public static void main(String[] args) throws Exception {
		Options options = new Options();

		options.addOption(OptionBuilder.withArgName("path").hasArg()
				.withDescription("efficiency topics location").create(INPUT_OPTION));
		options.addOption(OptionBuilder.withArgName("arg").hasArg()
				.withDescription("top k topics").create(TOP_OPTION));
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

		if (!cmdline.hasOption(INPUT_OPTION) || !cmdline.hasOption(TOP_OPTION) || !cmdline.hasOption(OUTPUT_OPTION)) {
			HelpFormatter formatter = new HelpFormatter();
			formatter.printHelp(FormatQuery.class.getName(), options);
			System.exit(-1);
		}

		String inputPath = cmdline.getOptionValue(INPUT_OPTION);
		File inputLocation = new File(inputPath);
		if (!inputLocation.exists()) {
			System.err.println("Error: " + inputLocation + " does not exist!");
			System.exit(-1);
		}
		int topN = Integer.parseInt(cmdline.getOptionValue(TOP_OPTION));
		String outputPath = cmdline.getOptionValue(OUTPUT_OPTION);
		BufferedWriter bw_query = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(outputPath)));
		try {
			FileInputStream fisTopics = new FileInputStream(inputPath);
			BufferedReader brTopics = new BufferedReader(new InputStreamReader(fisTopics));
			String line;
			int cnt = 0;
			while((line = brTopics.readLine()) != null) {
				cnt ++;
				String query = line.substring(line.indexOf(':') + 1);
				bw_query.write("<top>");
				bw_query.newLine();
				bw_query.write("<num> Number: MB" + cnt + " </num>");
				bw_query.newLine();
				bw_query.write("<title> " + query + " </title>");
				bw_query.newLine();
				bw_query.write("<querytime> Tue Feb 08 23:59:59 +0000 2011 </querytime>");
				bw_query.newLine();
				bw_query.write("<querytweettime> " + LAST_TWEET_TIME + " </querytweettime>");
				bw_query.newLine();
				bw_query.write("</top>");
				bw_query.newLine();
				bw_query.newLine();
				if (cnt == topN) {
					break;
				}
			}
			try {
				fisTopics.close();
				brTopics.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		bw_query.close();
	}
}
