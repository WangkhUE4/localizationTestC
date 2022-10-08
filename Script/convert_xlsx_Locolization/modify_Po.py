#coding=utf-8
import os, sys
import xlrd
import re

def ModifyPo(Lists,Language,PoPath):
    dic = {}
    index = Lists[0].index(Language)
    for i in Lists[0:]:
        dic.setdefault(i[1],i[index])

    h = open(PoPath,'r+',encoding='utf8')
    lines = h.readlines()
    for i in range(len(lines)):
        if (lines[i][0:7] == "#. Key:"):
            key = lines[i][8:-1]
            sStr = dic[key]
            
            if(dic[key]=="" and key.__contains__("PicBook_Story_PieceLegend_")):
                sStr = " "    
            if (str(dic[key]).endswith("\n")):
                lines[i+5] = "msgstr \"{a}\"".format(a = dic[key][:-1])
            else:
                lines[i+5] = "msgstr \"{a}\"".format(a = sStr)
            lines[i+5] = lines[i+5].replace('\n',r'\n') + '\n'

            i=i+7

    h.seek(0)
    h.writelines(lines)
    h.close()
    pass



def ConvertXLSX(xlsx,Lists):
    pat = re.compile("\{(\d):\S+?\}")
    for Data_sheet in xlsx.sheets()[1:]:
        rowNum = Data_sheet.nrows 
        colNum = Data_sheet.ncols 
        for i in range(rowNum):
            rowlist = []
            for j in range(colNum):
                #匹配解决 {0:00%} 等识别问题
                line = Data_sheet.cell_value(i, j)
                if isinstance(line,str):
                    line = pat.sub(r'{\1}',line)
                rowlist.append(line)
            rowlist[1] = rowlist[1].replace(" ","")
            Lists.append(rowlist)

def GetCombinValue(Lists,key,i,LanIndex):
    keylen = len(key)
    r = ''
    newi = max(0,i-100)
    newimax = min(i+100,len(Lists))
    newrange = newimax-newi
    for j in range(newrange):
        curlen = len(Lists[newi+j][1])
        lastlen = curlen-keylen
        if lastlen > 0 and lastlen < 4:
            curkey = Lists[newi+j][1][:keylen]
            if curkey == key:
                iii = Lists[newi+j][1][1-lastlen:]             
                try:
                    int(iii)
                except ValueError:
                    pass
                else:
                    if(int(iii)>0):
                        r += Lists[newi+j][LanIndex]+r"\n"
    if(len(r)>2):
        r = r[:-2]      
    return r


def CombinLists(Lists):

    LanguageNum = len(Lists[0])-3
    for i in range(len(Lists)):
        if Lists[i][1].endswith("_Count"):
            for LanIndex in range(LanguageNum):
                value = GetCombinValue(Lists,Lists[i][1][:-6],i,LanIndex+2)
                Lists[i][LanIndex+2] = value
            key = Lists[i][1][:-6]
            Lists[i][1] = key
            

# def CombinLists(Lists):

#     LanguageNum = len(Lists[0])
#     for LanIndex in range(LanguageNum):
#         for i in range(len(Lists)):
#             if Lists[i][1].endswith("_Count"):
#                 key = Lists[i][1][:-6]
#                 value = GetCombinValue(Lists,Lists[i][1][:-6],i,LanIndex+2)
#                 Lists[i][1] = key
#                 Lists[i][LanIndex+2] = value

pos = {
    "English": "/Content/Localization/Game/en/Game.po",
    "ChineseTraditional": "/Content/Localization/Game/zh-Hant/Game.po",
}

def main():

    if len(sys.argv) < 3:
        print("argv error")
        return

    xlsx_filePath = sys.argv[1]
    xlsx_file = xlrd.open_workbook(xlsx_filePath)
    Lists = []
    ConvertXLSX(xlsx_file,Lists)
    CombinLists(Lists)
    ProjectPath = sys.argv[2]
    
    for k in pos:
        ModifyPo(Lists,k,ProjectPath+pos[k])

if __name__ == "__main__":
    main()




#pip install xlrd==1.2.0
#pyinstaller  -F modify_Po.py 



