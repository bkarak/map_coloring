MAPFILES=$(wildcard map.*)

graphs:
	for file in $(MAPFILES); \
	do \
		./convert.pl $$file > $$file.dot ; \
		dot -Tgif -o $$file.gif $$file.dot ; \
	done

clean:
	-rm -f maps/*.gif
	-rm -f maps/*.dot