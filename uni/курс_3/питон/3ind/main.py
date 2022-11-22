import fileinput

n = 0; k = 0; l = 0; spu = 0; sh = 0
mu = [0]*100; a = [[0]*1000 for i in range(1001)]
c = [[0]*1000 for i in range(1001)]
b = [[0]*1000 for i in range(1001)]


def napr():
    global sh
    if (((c[k][l] < 1000) and (c[k][l] != 0)) or ((c[l][k] != 0) and (c[l][k] < 1000))):
        sh = 1


def pdele():
    global spu
    if (((a[k][l] >= 1000) or (a[k][l] == 0)) and ((a[l][k] == 0) or (a[l][k] >= 1000))):
        spu = 1

def Floyd():
    for i in range(1, n+1):
        for j in range(1, n+1):
            a[i][j] = b[i][j]
    for i in range(1, n + 1):
        a[i][i] = 0
    for u in range(1, n + 1):
        for i in range(1, n + 1):
            for j in range(1, n + 1):
                if(a[i][u] + a[u][j] < a[i][j]):
                    a[i][j] = a[i][u] + a[u][j]


def dele():
    for j in range(0, n):
        if(mu[j] != 0):
            x = mu[j]
            for i in range(1, n + 1):
                b[i][x] = 1000
                b[x][i] = 1000


def vosst():
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            b[i][j] = c[i][j]


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    t = 0
    print("Введите номер графа: ")
    graf = open("graf"+input() + ".txt", "r")
    rd = graf.readline().split()
    n = int(rd[0])
    for i in range(0, int(n)):
        mu[i] = 0
    for i in range(1, int(n)+1):
        for j in range(1, int(n)+1):
            c[i][j] = 1000
    m = int(rd[1])
    for j in range(1, int(m)+1):
        rd = graf.readline().split()
        c[int(rd[0])][int(rd[1])] = int(rd[2])
    print("Введите 2 вершины, для которых требуется найти множество: ")
    k = int(input())
    l = int(input())
    napr()
    if (sh == 0):
        if ((((l <= n) and (k <= n)) and ((l > 0) and (k > 0)))):
            if(k != l):
                vosst()
                Floyd()
                pdele()
                if (spu == 0):
                    while (spu == 0):
                        #print(1)
                        if ((t + 1 != l) and (t + 1 != k)):
                            t += 1
                        else:
                            if ((t + 2 != l) and (t + 2 != k)):
                                t = t + 2
                            else:
                                t = t + 3
                        mu[0] = t
                        po = 0
                        while (po != 1):
                            po = 1
                            for i in range(0, n):
                                if (mu[i] > n):
                                    mu[i] = mu[i] - n - 1
                                    if ((mu[i + 1] + 1 != l) and (mu[i + 1] + 1 != k)):
                                        mu[i+1] += 1
                                    else:
                                        if ((mu[i + 1] + 2 != l) and (mu[i + 1] + 2 != k)):
                                            mu[i + 1] = mu[i + 1] + 2
                                        else:
                                            mu[i + 1] = mu[i + 1] + 3
                                    po = 0
                        if t>n:
                            t = 0
                        vosst()
                        dele()
                        Floyd()
                        pdele()
                else:
                    print("Множество пустое, так как между заданными вершинами путь отсутствует изначатьно.")
            else:
                print("Номера заданных вершин одинаковы!")
            print("Множество вершин: ")
            for i in range (0, n):
                poo = 1
                for j in range(0, i):
                    if ((mu[j] == mu[i]) or (mu[i] == 0)):
                        poo = 0
                if poo == 1:
                    print(str(mu[i]) + " ")
        else:
            print("Введены слишком большие/малые значения номеров вершин!")
    else:
        print("Множество пустое, так как заданные вершины соединены дугой напрямую.")