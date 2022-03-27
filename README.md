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



### 2022.3.20 19:37

---

1. 上个版本存在无法识别如*1+3.4i*一类的数字，已修复
2. 修复第一个问题时出现段错误，经过gdb debug后发现，`addNode()`函数中使用了`vector::insert()`方法，容易造成越界导致段错误，已更改为`vector::push_back()`
3. 修改测试数据



**运行结果：**

<img src="image/task one2.png" style="zoom: 100%;float: left" />



### 2022.3.27 13:42

---

1. 调整文件结构
2. 结果输出在终端改为dump到文件夹中
3. 调整`run.sh`文件，增加运行多个task功能



<img src="image/run_3.27.png" alt="run_3.27" style="zoom:100%;float:left" />



### 2022.3.27 15:21

---

1. 增加语法分析器读取二型文法功能



**文件结构：**

. 
├── image 
│   ├── 2022.2.27.png 
│   ├── run_3.27.png 
│   ├── task one2.png 
│   └── task one.png 
├── lexical 
│   ├── convert.cpp 
│   ├── convert.h 
│   ├── header.h 
│   ├── lexer.cpp 
│   ├── lexer.h 
│   ├── lexical 
│   ├── lexical.cpp 
│   └── token.txt 
├── parser 
│   ├── header.h 
│   ├── parser.cpp 
│   └── parser.h 
├── README.md 
├── res 
├── run.sh 
└── simulation 
    ├── grammar.txt 
    └── test.txt 

5 directories, 19 files 

