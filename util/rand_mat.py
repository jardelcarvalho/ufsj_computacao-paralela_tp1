import sys
import random


p = [4, 9]


# matrizes múltiplas de q (cond. Fox)
mult = 1
for q in list(map(lambda x: int(x ** .5), p)):
    mult *= q

path = sys.argv[1]
dim = mult
while (dim * 2) ** 2 / 10 ** 6 < 10:
    dim *= 2
    print(dim)
    with open(path + '/' + str(dim) + 'x' + str(dim) + '.txt', 'w') as f:
        f.write(str(dim) + '\n')
        for i in range(dim):
            for j in range(dim):
                if i != j:
                    f.write(str(random.randint(0, 100)))
                else:
                    f.write('0')
                if j == dim - 1:
                    f.write('\n')
                    continue
                f.write(' ')


        
