#/bin/bash

cd ../floyd-warshall_fox_openmpi

make

for mat in "$matrizes"../util/mat/*
do
    for i in {1..10}
    do
	echo $mat "i="$i", p = 1"
        mpirun -np 1 -hostfile ../util/hostfile main $mat
        echo $mat "i="$i", p = 4"
        mpirun -np 4 -hostfile ../util/hostfile main $mat
        echo $mat "i="$i", p = 9"
        mpirun -np 9 -hostfile ../util/hostfile main $mat
        echo "/"
    done
done

make clean



echo "terminou"

