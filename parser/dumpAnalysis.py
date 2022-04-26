import xlwt

actionGoto_txt =open('../res/parser/statistics/actionGoto.txt')
actionGoto=[]
temp0 = actionGoto_txt.readlines()
for line in temp0:
    str = line.rstrip().split()
    actionGoto.append(str)

stateStack_txt =open('../res/parser/statistics/stateStack.txt')
stateStack=[]
temp1 = stateStack_txt.readlines()
for line in temp1:
    str = line.rstrip().split()
    stateStack.append(str)

symbolStack_txt =open('../res/parser/statistics/symbolStack.txt')
symbolStack=[]
temp2 = symbolStack_txt.readlines()
for line in temp2:
    str = line.rstrip().split()
    symbolStack.append(str)

inputStr_txt =open('../res/parser/statistics/inputStr.txt')
inputStr=[]
temp3 = inputStr_txt.readlines()
for line in temp3:
    str = line.rstrip().split()
    inputStr.append(str)

maxStateLen = 0
for i in range(len(stateStack)):
    tempLen = len(stateStack[i])
    if(tempLen > maxStateLen):
        maxStateLen = tempLen

maxSymbolLen = 0
for i in range(len(symbolStack)):
    tempLen = len(symbolStack[i])
    if(tempLen > maxSymbolLen):
        maxSymbolLen = tempLen

maxStrLen = 0
for i in range(len(inputStr)):
    tempLen = len(inputStr[i])
    if(tempLen > maxStrLen):
        maxStrLen = tempLen

wb = xlwt.Workbook()
ws = wb.add_sheet('analysis sheet')

ws.write(0, 0, '步骤')
style = xlwt.XFStyle()
al = xlwt.Alignment()
al.horz = 0x02
style.alignment = al
ws.write_merge(0, 0, 1, maxSymbolLen, '符号栈', style)
ws.write_merge(0, 0, maxSymbolLen + 3, maxSymbolLen + 2 + maxStateLen, '状态栈', style)
ws.write_merge(0, 0, maxSymbolLen + maxStateLen + 5, maxSymbolLen + maxStateLen + 4 + maxStrLen, '状态栈', style)
ws.write(0, maxSymbolLen + maxStateLen + maxStrLen + 7, 'ACTION')
ws.write(0, maxSymbolLen + maxStateLen + maxStrLen + 8, 'GOTO')


for i in range(len(stateStack)):
    ws.write(i + 1, 0, i + 1)
    for j in range(maxStateLen):
        if(j < len(stateStack[i])):
            ws.write(i + 1, j + 1, stateStack[i][j])
        else:
            ws.write(i + 1, j + 1, ' ')
    ws.write(i + 1, maxStateLen + 1, ' ')
    ws.write(i + 1, maxStateLen + 2, ' ')
    for j in range(maxSymbolLen):
        if(j < len(symbolStack[i])):
            ws.write(i + 1, maxStateLen + 3 + j, symbolStack[i][j])
        else:
            ws.write(i + 1, maxStateLen + 3 + j, ' ')
    ws.write(i + 1, maxStateLen + maxSymbolLen + 2 + 1, ' ')
    ws.write(i + 1, maxStateLen + maxSymbolLen + 2 + 2, ' ')
    for j in range(maxStrLen):
        if(j < len(inputStr[i])):
            ws.write(i + 1, maxStateLen + maxSymbolLen + 2 + 3 + j, inputStr[i][j])
        else:
            ws.write(i + 1, maxStateLen + maxSymbolLen + 2 + 3 + j, ' ')
    ws.write(i + 1, maxStateLen + maxSymbolLen + maxStrLen + 2 + 2 + 1, ' ')
    ws.write(i + 1, maxStateLen + maxSymbolLen + maxStrLen + 2 + 2 + 2, ' ')
    ws.write(i + 1, maxStateLen + maxSymbolLen + maxStrLen + 2 + 2 + 3, actionGoto[i][0])
    ws.write(i + 1, maxStateLen + maxSymbolLen + maxStrLen + 2 + 2 + 4, actionGoto[i][1])

wb.save('../res/parser/statistics/analysis.xls')