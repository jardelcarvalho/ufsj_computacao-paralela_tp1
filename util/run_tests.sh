#/bin/bash

cd ../sequencial

make

for mat in "$matrizes"../util/mat/*
do
    for i in {1..10}
    do
    ./main $mat
    done
done

make clean

cd ../paralelo

make

for mat in "$matrizes"../util/mat/*
do
    for i in {1..10}
    do
        mpirun -np 4 -f ../util/hostfile main $mat
        mpirun -np 9 -f ../util/hostfile main $mat
    done
done

make clean

echo "terminou"

