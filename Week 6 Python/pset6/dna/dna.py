from sys import argv
from cs50 import get_string

if len(argv) != 3:
    exit("Usage: python dna.py")

DBfile = open(argv[1], 'r')

strands = []
persons = {}

for index, row in enumerate(DBfile):
    if index == 0:
        strands = [strand for strand in row.strip().split(',')][1:]
    else:
        currRow = row.strip().split(',')
        persons[currRow[0]] = [int(x) for x in currRow[1:]]

DNAstrand = open(argv[2], 'r').read()

finalStrands = []
for strand in strands:
    i = 0
    maxStrand = 0
    currMax = 0
    while i < len(DNAstrand):
        currSearch = DNAstrand[i: i + len(strand)]
        if currSearch == strand:
            currMax += 1
            maxStrand = max(maxStrand, currMax)
            i += len(strand)
        else:
            currMax = 0
            i += 1
    finalStrands.append(maxStrand)

for name, data in persons.items():
    if data == finalStrands:
        print(name)
        exit()


print("No match")
