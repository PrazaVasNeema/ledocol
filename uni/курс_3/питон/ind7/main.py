from lxml import etree as et


PATH = '1.osm'

supermarkets = {}


data = open(PATH, 'r', encoding='utf-8').readlines()

root = et.fromstringlist(data)

for appt in root.getchildren():
    if appt.tag == 'node':
        flag = False
        for elem in appt.getchildren():
            if elem.get('v') == 'supermarket':
                flag = True
        if flag:
            for elem in appt.getchildren():
                if elem.get('k') == 'name':
                    if elem.get('v') in supermarkets:
                        supermarkets[elem.get('v')] += 1
                    else:
                        supermarkets[elem.get('v')] = 1
print(supermarkets)



