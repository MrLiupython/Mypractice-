def yanghuis(n):
    if n < 0:
        print("invalid query")
    else:
        Y = []
        for t in range(n+1):
            Y.append([0 for t2 in range(t+1)])
        i = 0
        while i <= n:
            for j in range(i+1):
                if j == 0 or j == i:
                    Y[i][j] = 1
                else:
                    Y[i][j] = Y[i-1][j-1] + Y[i-1][j]
            i = i+1
    return Y
def yanghui(m,n):
    if n < 1 or n > m+1:
        print("invalid query")
    else:
        y=yanghuis(m)
    print(y[m][n-1])
def yanghui_yh(m):
    y=yanghuis(m)
    for t in y:
        for t2 in t:
            print(t2,end='')
            print(' ',end='')
        print('')
