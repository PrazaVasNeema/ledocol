sentence = input().replace('.', '').replace('?', '').replace('!', '').replace(',','').split()
counter = {}
max = 1;
for word in sentence:
    if word in counter:
        counter[word] += 1
        if counter[word] > max:
            max += 1
    else:
        counter[word] = 1

s = [k for k,v in counter.items() if v == max]
s = sorted(s)
print(s[0] + ' [' + str(counter[s[0]]) + ']')
