from lxml import etree as et


PATH = '2.osm'

counter = 0

data = open(PATH, 'r', encoding='utf-8').readlines()

root = et.fromstringlist(data)

for appt in root.getchildren():
    for elem in appt.getchildren():
        if elem.get('k') == 'shop' and elem.get('v') != 'supermarket':
            counter += 1
print(counter)
