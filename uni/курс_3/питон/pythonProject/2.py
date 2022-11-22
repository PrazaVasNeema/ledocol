
n = int(input())
states = dict()
for i in range(n):
    a = input().split()
    states[a[0]] = int(a[1])

elections = dict()
condidates = []
for i in states:
    elections[i] = {}
m = int(input())
for i in range(m):
    a = input().split()
    if a[1] not in condidates:
        condidates.append(a[1])
    elections[a[0]][a[1]] = elections[a[0]].get(a[1], 0) + 1

for i in elections:
    r_t = sorted(elections[i].items(), key=lambda item: item[0])
    elections[i] = max(r_t, key=lambda x: x[1])[0]

results = dict()
for i in elections:
    results[elections[i]] = results.get(elections[i], 0) + states[i]
    condidates.remove(elections[i])
condidates.sort()
for i in results:
    print(i, results[i])
for i in condidates:
    print(i, 0)