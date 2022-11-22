sentence_input = input().replace('.', ' . ').replace('?', ' ? ').replace('!', ' ! ').replace(',', ' , ').split()
sentence_output = ''
occur = {}
for word in sentence_input:
    if not (word.isalpha() or word.isdigit()):
        sentence_output += word
        continue
    if word in occur:
        occur[word] += 1
    else:
        occur[word] = 1
    sentence_output += ' ' + word + '[' + str(occur[word] - 1) + ']'
print(sentence_output)
