s = input().split('.')[0].replace(' ', '').upper()
s = ''.join([i for i in s if not i.isdigit()])
s = sorted(s , reverse = True)

res = ''
check_imp = False
center = 0
res = ''
i = 0
while(i < len(s)):
    if (check_imp):
        break
    if (s.count(s[i]) % 2 == 1):
        if (center):
            check_imp = True
            break
        center = s[i]
    res = res.ljust(s.count(s[i]) // 2 + len(res), s[i])
    i += s.count(s[i]) - 1
    i += 1

if(check_imp):
    print('Нет')
else:
    print('Да')
    temp = res
    if(center):
        res += center
    res += temp[::-1]
    print(res)

#Deed daad N.