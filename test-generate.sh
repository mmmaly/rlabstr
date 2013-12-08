make rlabstr-all
make maze-generator

for((i=4;i<40;i++)); do echo $i; ./maze-generator $i $i > maze.in.$i; time ionice -c 3 chrt -i 0 ./rlabstr-all maze.in.$i > maze.in.$i.log 2>&1 ; mkdir maze.$i; mv hist* maze.in.$i* statistics.log current.maze maze.$i; done
