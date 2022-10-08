#coding=utf-8
import os, sys
import xlrd
import re

def ModifyPo(Lists,Language,PoPath):
    dic = {}
    index = Lists[0].index(Language)
    for i in Lists[1:]:
        dic.setdefault(i[1],i[index])

    h = open(PoPath,'r+',encoding='utf8')
    lines = h.readlines()
    for i in range(len(lines)):
        if (lines[i][0:7] == "#. Key:"):
            key = lines[i][8:-1]
            if (str(dic[key]).endswith("\n")):
                lines[i+5] = "msgstr \"{a}\"\n".format(a = dic[key][:-1])
            else:
                lines[i+5] = "msgstr \"{a}\"\n".format(a = dic[key])
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
    
    

def GetCombinValue(Lists,key,i):
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
                        r += Lists[newi+j][2]+r"\n"
                    
    if(len(r)>2):
        r = r[:-2]   
    return r

        

def SaveStringTable(Lists,csv_filePath):
    h = open(csv_filePath,'w',encoding='utf8')
    h.write('Key,SourceString\n')

    for i in range(len(Lists)):
        #解决 key为空的问题
        if Lists[i][1] == "":
            pass
        elif Lists[i][1].endswith("_Count"):
            key = Lists[i][1][:-6]
            value = GetCombinValue(Lists,Lists[i][1][:-6],i)
            h.write('{k},"{v}"\n'.format(k=key,v=value))
            pass
        else:
            h.write('{k},"{v}"\n'.format(k=Lists[i][1],v=Lists[i][2]))
    h.close()






pos = {
    "English": "/Content/Localization/Game/en/Game.po",
    "ChineseTraditional": "/Content/Localization/Game/zh-Hant/Game.po",
}

def main():



    if len(sys.argv) < 2:
        print("argv error")
        return

    xlsx_filePath = sys.argv[1]
    csv_filePath = sys.argv[1].replace("xlsx","csv")
    xlsx_file = xlrd.open_workbook(xlsx_filePath)
    Lists = []
    ConvertXLSX(xlsx_file,Lists)
    SaveStringTable(Lists,csv_filePath)

   # ProjectPath = sys.argv[2]
    
   # for k in pos:
   #     ModifyPo(Lists,k,ProjectPath+pos[k])

if __name__ == "__main__":
    main()




#pyinstaller  -F convert_xlsx_Locolization.py




