#!/usr/bin/perl
#
# Perl script that transforms the input map format to Graphviz dot file
#
# Vassilios Karakoidas - bkarak@aueb.gr
#
# DISCLAIMER - This software is free, use this at your own risk
#

open(GRAPH,$ARGV[0]) or die;
print "digraph G {\n";
print "edge [arrowhead=none,arrowtail=none];\n";
while(<GRAPH>){
	if(/([0-9]+)[ ]+([0-9]+)/) {
		print "\t".$1." -> ".$2."\n";
	}
}
print "}\n";
close(GRAPH);
