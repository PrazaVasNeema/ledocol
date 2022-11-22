n = int(input())
game = {}
no_count = 0;
game_exit = False
cur_qst = []
yes_count = n // 2 + 1
yes_count_temp = 0
no_count = 0
while True:
    s = input()
    s_list = s.split()
    cur_qst = []
    yes_count_temp = 0
    show = False
    i = 0
    while i < len(s_list):
        try:
            if s_list[i] == 'help':
                game_exit = True
                break
            if s_list[i] == 'show':
                show = True
                break
            int(s_list[i])
            cur_qst+=str(s_list[i])
        #            print(a[int(char)])
        except ValueError:
            pass
        i += 1
    if show:
        print(game)
        continue
    if game_exit:
        break
    if len(cur_qst) == yes_count / 2:
        print("NO")
        continue


    for i in range (0, len(cur_qst)):
        if cur_qst[i] in game:
            if game[cur_qst[i]] == "NO":
                continue
        yes_count_temp += 1

    print(yes_count_temp)
    print(yes_count)

    if yes_count_temp > yes_count // 2:
        answer = "YES"
        for i in range (0, len(cur_qst)):
            if not cur_qst[i] in game:
                game[cur_qst[i]] = "YES"
        for i in range (1, n+1):
            if not str(i) in game:
                game[str(i)] = "NO"
                no_count += 1
            if str(i) in game:
                if cur_qst.count(str(i)) == 0 and game[str(i)] == "YES":
                    game[str(i)] = "NO"
                    no_count += 1
        yes_count = yes_count_temp
    else:
        answer = "NO"
        for i in range (0, len(cur_qst)):
            if not cur_qst[i] in game:
                game[cur_qst[i]] = "NO"
                no_count += 1
        yes_count = (n - no_count) // 2 + 1
    print(answer)
print(game)