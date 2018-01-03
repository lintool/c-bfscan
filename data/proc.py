file = open("qrels.microblog2011-2012.txt")
file_to = open("qrels.txt", "a")
lines = file.readlines()
for line in lines:
	line = line.strip().split()
	file_to.write('MB%02d %s %s %s\n' % (int(line[0]), line[1], line[2], line[3]))
