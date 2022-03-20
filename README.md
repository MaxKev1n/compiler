# compiler

### 2022.2.26 15:53

---

完成三型文法至DFA的转换



### 2022.2.26 20:23

---

代码存在部分问题，完成已知的bug修复 

**由于编译问题，暂时将所有文件放在`new.cpp`和`new.h`中** 

目前进展：可以将合法的字符组成(以下划线和字母为首)正确分割


### 2022.2.26 21:18

---

修复编译问题，重新组织文件结构

.  
├── convert.cpp  
├── convert.h  
├── header.h  
├── lexer.cpp  
├── lexer.h  
├── README.md  
├── simulation  
│   ├── grammar.txt  
│   └── test.txt  
├── test  
└── test.cpp  

1 directory, 10 files



### 2022.2.27 13:53

---

完成DFA最小化，并且可以输出具体的DFA列表，输出结果如图

<img src="image/2022.2.27.png" style="zoom: 67%;float: left" />



### 2022.2.27 14:02

---

**新增加部分词法规则**  

1. 科学计数法
2. 复数常量



### 2022.3.6 20:38

---

1. 修复部分bug
2. 需要添加运算epsilon-closure的功能，并修改数字的正则文法



### 2022.3.20 17:48

---

1. 完成添加epsilon-closure的功能
2. 修改正则文法，以达到任务一目标
3. 增加识别类型函数
4. 增加识别运算符功能
5. 添加运行脚本`run.sh`



**运行截图：**

<img src="image/task one.png" style="zoom: 100%;float: left" />

