# compiler

### 2022.2.16 15:53

---

完成三型文法至DFA的转换



### 2022.2.16 20:23

---

代码存在部分问题，完成已知的bug修复 

**由于编译问题，暂时将所有文件放在`new.cpp`和`new.h`中** 

目前进展：可以将合法的字符组成(以下划线和字母为首)正确分割


### 2022.2.16 21:18

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
