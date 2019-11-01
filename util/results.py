import numpy as np
import matplotlib.pyplot as plt

def floats(_str):
    t = []
    j = 0
    for i, c in enumerate(_str):
        if c == '\n' and j - i != 0:
            t += [float(_str[j: i])]
            j = i + 1
    t += [float(_str[j: -1])]
    return t

tests = [12, 24, 48, 96, 192, 384, 768, 1536]

vt1, vt4, vt9 = [], [], []
for N in tests:
    with open('time_res/T(1)_' + str(N) + 'x' + str(N) + '.txt') as f:
        vt1 += [floats(f.read())]
    with open('time_res/T(4)_' + str(N) + 'x' + str(N) + '.txt') as f:
        vt4 += [floats(f.read())]
    with open('time_res/T(9)_' + str(N) + 'x' + str(N) + '.txt') as f:
        vt9 += [floats(f.read())]

mt1, mt4, mt9, dt1, dt4, dt9 = [], [], [], [], [], [] 
for p, q, r in zip(vt1, vt4, vt9):
    mt1 += [np.mean(p)]
    mt4 += [np.mean(q)]
    mt9 += [np.mean(r)]
    dt1 += [np.std(p)]
    dt4 += [np.std(q)]
    dt9 += [np.std(r)]

plt.plot(tests, mt1, marker='^', color='red', label='T(1)', lw=.5, markersize=4)
plt.plot(tests, mt4, marker='.', color='blue', label='T(4)', lw=.5, markersize=4)
plt.plot(tests, mt9, marker='+', color='green', label='T(9)', lw=.5, markersize=4)

plt.xticks([12, 192, 1536])
plt.xlabel('Entrada (N)')
plt.ylabel('Tempo (s)')

plt.legend()
plt.show()

su1, su4, su9 = [], [], []
for p, q, r in zip(mt1, mt4, mt9):
    su1 += [1]
    su4 += [p / q]
    su9 += [p / r]

bw = .10
plt.bar([x - bw * (1.03) for x in range(1, 9, 1)], su1, width=bw, label='p = 1')
plt.bar([x for x in range(1, 9, 1)], su4, width=bw, label='p = 4')
plt.bar([x + bw * (1.03) for x in range(1, 9, 1)], su9, width=bw, label='p = 9')

plt.xlabel('Entrada (N)')
plt.ylabel(r'Speedup $\frac{T(1)}{T(p)}$')
plt.xticks([x for x in range(1, 9, 1)], tests)
plt.legend()
plt.show()

for m in [mt1, mt4, mt9]:
    for v in m:
        print("{0:0.6f}".format(v))
    print('\n')

for N in tests:
    print(str(N) + 'x' + str(N))