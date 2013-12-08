#SHELL=/usr/bin/bash

test: rlabstr-all maze.in
	screen bash -c "time ionice -c 3 chrt -i 0 ./rlabstr-all maze.in ; read"
	screen tailf statistics.log
	screen watch -d -n 0.5 cat current.maze

#generate: maze-generator
#	./maze-generator 20 21 > maze.in

maze-generator: maze-generator.cpp
	g++ -Wall -pedantic maze-generator.cpp -o maze-generator


rlabstr-all: rlabstr-all.cpp params.h
	g++ -Wall -Werror -pedantic rlabstr-all.cpp -o rlabstr-all

svgs:
	for i in *.dot; do echo $$i; dot -Kneato -Tsvg -o $${i%dot}svg $$i;	done

pdfs:
	for i in *.svg; do echo $$i; inkscape $$i --export-pdf=$${i%.svg}.pdf; done	

rsync-get:
	rsync --update -avzP --exclude "history_*" -e "ssh -i rsync-cpp-rlabstr -l mmm" mmm:/home/mmm/cpp/rlabstr ~/code/

rsync-put:
	rsync --update -avzP --exclude "history_*" -e "ssh -l mmm" ~/code/rlabstr mmm:~/cpp/

kill:
	killall rlabstr-all ; kill `ps -C tailf -o pid,command | grep "tailf statistics.log" | awk '{print $$1}'` ; 	kill `ps -C watch -o pid,command | grep "watch -d -n 0.5 cat current.maze" | awk '{print $$1}'`

clean:
	rm -f *.maze *.dot history.out history.txt hist.cnf.test statistics.log timelimit.txt rlabstr-all
