# corruptor

CC=gcc

all: exec test
	
exec:
	gcc ctr.c ctr_exec.c -o ctr

test: 
	gcc ctr.c unittest.c -o unittest

clean:
	rm target/nested/*
	#cp mp3/* target/nested/
	cp mp3/Bebe_-_Malo.mp3 target/nested/20190101-1.mp3
	cp mp3/bebe_-_Siempre_Me_Quedara_Cocain.mp3 target/nested/20190101-2.mp3
	cp mp3/empty.mp3 target/nested/20190101-3.mp3
	touch target/nested/other-file
	
	touch ctr; rm ctr
	touch unittest; rm unittest
	touch ctr.log; rm ctr.log