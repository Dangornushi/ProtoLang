import sys

class Run:
    def __init__(self):
        self.wc = 0

    def run(self, i):
        file = open(sys.argv[1], encoding="utf-8")
        data2 = file.readlines()

        dick = {}
        lis = []
        lisf = []
        lisw = []
        wc = 0
        ji = 0
        vald = {}

        for data in data2:
            data = data.replace("\n", "")
            if data.startswith("    "):
                if wc == 1:
                    lisw.append(data.replace("    ", "") + ";")
                else:
                    lis.append("{};".format(data.replace("    ", "")))
            
            elif data.startswith("    ret"):
                break
            
            elif data.endswith(":"):
                if data.startswith("_"):
                    try:
                    
                        try:
                            ji = int(data.split(" ")[1].replace(":", ""))
                    
                        except IndexError:
                            ji = int(vald[data.split(" ")[1].replace(":", "")])
                    
                    except ValueError:
                        ji = "True"

                func = data.replace(":", "").split("(")[0]
                lisf.append(func)

            elif data.startswith("call"):
                dick2 = dict(zip(lisf, "".join(lis).split("fin")))
                dick.update(dick2)
                self.Main(dick, vald, data.split(" ")[1], i, ji, 1)

        file.close()
    
    def Main(self, dick, vald, f, i, ji, fori2):
        lis = str(dick[f]).split(";")
        lisf = f
        fori = 1
        for data in lis:
            data = data.split(";")
            data = [a for a in data if a != '']

            for data in data:
                if data.endswith(")") and data.startswith("call") is False and data.startswith("mov") is False:
                    val = data.split("msg ")[1].split("(")[0]+"("+data.split("(")[1]
                    if '"' in val:
                        print(val.replace('"', ""))
                    
                    elif data.endswith(")"):
                        self.Main(dick, vald, val, i, ji, fori2)
                        print(vald[vald[val]])
                    else:
                        self.Main(dick, vald, val, i, ji)
                        print(vald[val])

                elif data.startswith("ret "):
                    func = data.split(", ")[0].split(" ")[1].split("(")[1]
                    vald[func] = data.split(", ")[1]
                else:
                    data = str(data)
                    if data.startswith("mov"):
                        if data.split(" ")[1] == "end":
                            break
                        
                        else:
                            val = "".join(data.split(", ")[0].split(" ")[1])
                            if data.endswith("]"):
                                try:
                                    arg = len(list(data.split(":")[1]))
                                except IndexError:
                                    arg = "["+data.split("[")[1]
                            else:
                                arg = data.split(", ")[1]
                            
                            if data.endswith(")"):
                                self.Main(dick, vald, val.split("(")[1], i, ji, fori2)
                            
                        try:
                            vald[val] = vald[arg]
                        except KeyError:
                            vald[val] = arg
                    
                    elif data.startswith("syp"):
                        sys.stdout.write(data.split(":")[1])
            
                    elif data.startswith("syf"):
                        sys.stdout.flush()
                    
                    elif data.startswith("time"):
                        import time
                        time.sleep(eval(data.split(":")[1]))

                    elif data.startswith("strf"):
                        vald[data.split(", ")[0].split(" ")[1]] = data.split(", ")[1]

                    elif "open" in data:
                        name = "".join(data.split(":")[1:]).replace(" ", "").split(",")
                        opf = open(vald[name[0]], name[1], encoding=name[2])
                        
                    elif data.endswith("close"):
                        opf.close()

                    elif data.endswith("make"):
                        file = data.split(" ")[1]
                        with open(file.replace(",", ""), "w", encoding="utf_8") as opf:
                            pass
                    
                    elif "write" in data:
                        opf.write("".join(data.split(":")[1]))

                    elif data.startswith("pop "):
                        arg2 = data.replace("pop ", "").replace(";", "")
                        if arg2 == "":
                            break

                        else:
                            if len(vald) < fori2:
                                fori2 = 1
                                break

                            else:
                                vald[arg2] = vald[fori2]
                                fori2 += 1

                    elif data.startswith("call"):
                        func = data.split(" ")[1].split("(")[0]
                        func2 = data.split(" ")[1]
                        if func.endswith("()"):
                            pass
                        else:
                            argn = data.split("(")[1].replace(")", "").replace(" ", "").split(",")
                            arg = func2.split("(")[1].replace(")", "").replace(",", "")
                            vald2 = {}
                            
                            for lis in argn:
                                vald2[fori] = vald[lis]
                                fori += 1
                        self.Main(dick, vald2, func, i, ji, fori2)

                    elif data.startswith("msg"):
                        #TODO
                        if ' "' in data.split("msg")[1]:
                            print(data.split("msg")[1].replace(' "', "").replace('"', ""))

                        else:
                            dick2 = {}
                            try:
                                dick2["1"] = vald["".join(data.split("msg ")[1:])]
                                self.Main(dick2, vald, "1", i, ji, fori2)
                                if str(vald[data.split("msg ")[1]]).startswith("open"):
                                    pass
                                else:
                                    try:
                                        self.Main(dick, vald, vald[vald[data.split("msg ")[1]]], i, ji, fori2)
                                        print(dick[vald[vald[data.split("msg ")[1]]]])
                                    except KeyError:
                                        print(vald["".join(data.split("msg ")[1:])])
                            except KeyError:
                                cou = 0
                                while True:
                                    cou += 1
                                    try:
                                        vald[data.split("msg ")[1]] = vald[cou]
                                        print(vald[data.split("msg ")[1]])
                                        break
                                    except KeyError:
                                        pass
                                
                    elif data.startswith("add"):
                        formula = data.split(",")[1].replace(" ", "")
                        formula2 = data.split(",")[2].replace(" ", "")
                        val = data.split(",")[0].split(" ")[1]
                        try:
                            vald[val] = int(vald[formula]) + int(vald[formula2])

                        except KeyError:

                            try:
                                vald[val] = int(vald[formula]) + int(formula2)
                            except KeyError:
                                vald[val] = int(formula) + int(vald[formula2])

                    elif data.startswith("sub"):
                        formula = data.split(",")[1].replace(" ", "")
                        formula2 = data.split(",")[2].replace(" ", "")
                        val = data.split(",")[0].split(" ")[1]
                        try:
                            vald[val] = int(vald[formula]) - int(vald[formula2])

                        except KeyError:

                            try:
                                vald[val] = int(vald[formula]) - int(formula2)

                            except KeyError:
                                vald[val] = int(formula) - int(formula2)

                    elif data.startswith("mul"):
                        formula = data.split(",")[1].replace(" ", "")
                        formula2 = data.split(",")[2].replace(" ", "")
                        val = data.split(",")[0].split(" ")[1]
                        try:
                            vald[val] = int(vald[formula]) * int(vald[formula2])

                        except KeyError:

                            try:
                                vald[val] = int(vald[formula]) * int(formula2)

                            except KeyError:
                                vald[val] = int(formula) * int(vald[formula2])

                    elif data.startswith("div"):
                        formula = data.split(",")[1].replace(" ", "")
                        formula2 = data.split(",")[2].replace(" ", "")
                        val = data.split(",")[0].split(" ")[1]
                        try:
                            vald[val] = int(vald[formula]) / int(vald[formula2])

                        except KeyError:

                            try:
                                vald[val] = int(vald[formula]) / int(formula2)

                            except KeyError:
                                vald[val] = int(formula) / int(vald[formula2])

                    elif data == "break":
                        break

                    elif data.startswith("jmp"):
                        jmp = data.replace("jmp ", "")
                        try:
                            if ji == "True":
                                while True:
                                    self.Main(dick, vald, jmp, i, "True", fori2)

                            else:
                                try:
                                    ji = int(vald[data.split(", ")[1]])
                                except KeyError:
                                    ji = int(data.split(", ")[1])
                                for dan in range(ji):
                                    self.Main(dick, vald, jmp, i, 0, fori2)
                        except KeyError:
                            pass

                    elif data.startswith("jne"):
                        data = data.replace(",", "").split(" ")
                        func = data[3]
                        try:
                            elfunc = data[4]
                        except IndexError:
                            elfunc = ""
                        try:
                            if int(vald[data[1]]) > int(vald[data[2]]):
                                self.Main(dick, vald, func, i, ji, fori2)
                            
                            else:
                                break

                        except KeyError:
                            try:
                                if int(vald[data[1]]) > int(data[2]):
                                    self.Main(dick, vald, func, i, ji, fori2)
                                else:
                                    break

                            except KeyError:
                                if int(data[1]) > int(vald[data[2]]):
                                    self.Main(dick, vald, func, i, ji, fori2)
                                else:
                                    break

                    elif data.startswith("ja"):
                        data = data.replace(",", "").split(" ")
                        func = data[3]
                        nextfunc = "L"+str(int(func.split("L")[1])+1)
                        try:
                            elfunc = data[4]
                        except IndexError:
                            self.Main(dick, vald, nextfunc, i, ji, fori2)
                        try:
                            if int(vald[data[1]]) < int(vald[data[2]]):
                                self.Main(dick, func, i, ji, fori2)
                            else:
                                self.Main(dick, vald, nextfunc, i, ji, fori2)
                                break

                        except KeyError:
                            try:
                                if int(vald[data[1]]) < int(data[2]):
                                    self.Main(dick, vald, func, i, ji, fori2)
                                else:
                                    self.Main(dick, vald, nextfunc, i, ji, fori2)
                                    break

                            except KeyError:
                                if int(data[1]) < int(data[2]):
                                    self.Main(dick, vald, func, i, ji, fori2)
                                else:    
                                    self.Main(dick, vald, vald, nextfunc, i, ji, fori2)
                                    break
                    
                    elif data.startswith("exit"):
                        sys.exit()

if __name__ == '__main__':
    Run().run(0)
