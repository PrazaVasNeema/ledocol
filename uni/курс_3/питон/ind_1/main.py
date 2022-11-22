'''
txt = "h3110 23 cat 444.4 rabbit 11 2 dog"
l = []
for t in txt:
    try:
        l.append(int(t))
    except ValueError:
        pass
print(l)
[int(s) for s in txt.split() if s.isdigit()]
l = [c for c in txt]
print(l)
'''
#for i:=99921 downto 20
a=[]
a=[0]*10
s=input()
d=''
while True:
    for char in s:
        try:
            if char=='0':
                s = '0'
                break
            a[int(char)] += 1
#            print(a[int(char)])
        except ValueError:
            pass
    if s=='0':
        break
    s=input()
for i in range(1,10):
    if a[i]>=2:
        for j in range(0,a[i]//2):
            d+=str(i)
temp = d[::-1]
for i in range(0,10):
    if a[i]%2==1:
        d+=str(i)
        break
d+=temp
print(d)