import sys

# compara matrizes através da igualdade dos arquivos
mat_n = mat_m = ''
with open(sys.argv[1], 'r') as m:
    _str = m.read()
    for c in _str:
        if c == '\n':
            mat_m += ' '
        else:
            mat_m += c

with open(sys.argv[2], 'r') as n:
    _str = n.read()
    for c in _str:
        if c == '\n':
            mat_n += ' '
        else:
            mat_n += c

if len(mat_m) != len(mat_n):
    print('diferentes')
    exit(0)

for c, _c in zip(mat_m, mat_n):
    if c != _c:
        print('diferentes')
        exit(0)

print('iguais')
        
        
            
        
        