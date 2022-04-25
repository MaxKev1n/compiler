import xlwt
import xlrd

terminals_txt =open('../res/parser/Terminals.txt')
terminals=[]
for line in terminals_txt:
    terminals.append(line.strip())

nonTerminals_txt =open('../res/parser/nonTerminals.txt')
nonTerminals=[]
for line in nonTerminals_txt:
    nonTerminals.append(line.strip())
del nonTerminals[0]

closure_txt =open('../res/parser/action&goto table.txt')
closures=[]
for line in closure_txt:
    closures.append(line.strip())
closure_num = int(closures[0])
del closures[0]

wb = xlwt.Workbook()
ws = wb.add_sheet('action&goto sheet')

ws.write(0, 0, '状态')
index = 1
for terminal in terminals:
    ws.write(0, index, terminal)
    index = index + 1

ws.write(0, index, ' ')
index = index + 1

for nonTerminal in nonTerminals:
    ws.write(0, index, nonTerminal)
    index = index + 1

length = len(terminals) + len(nonTerminals) + 2
for row in range(closure_num):
    for column in range(length):
        ws.write(row + 1, column, closures[row * length + column])


wb.save('../res/parser/action&goto table.xls')