# Asembler Project
This program convert asember code into object code.

- ![asembler code](https://github.com/gwnuysw/AssemblerProject/blob/master/SystemProgramming_Asembler_20141640%EC%9D%B4%EC%84%9D%EC%9B%90/%EC%BA%A1%EC%B2%98%EC%82%AC%EC%A7%84/asemblerCode.PNG)*asembler code*
- ![Object code](https://github.com/gwnuysw/AssemblerProject/blob/master/SystemProgramming_Asembler_20141640%EC%9D%B4%EC%84%9D%EC%9B%90/%EC%BA%A1%EC%B2%98%EC%82%AC%EC%A7%84/ObjectProgram%EC%BA%A1%EC%B3%90.PNG)*Object code*

## File organization
- Objectprogram
- asemfile
- readline.c(Open 'asemfile' to read a text line. path1, path2 use this function)
- path1.c(Check every text line to see if label or command are valid, store label data of asembler code)
- path2.c(Combine object code to make 'Objectprogram')
- asembler.c(Call path1, path2)
- charAnalisys.c(All function for path2)


## Basic algorithm of path1
<!--
![path1 algo](https://github.com/gwnuysw/AssemblerProject/blob/master/SystemProgramming_Asembler_20141640%EC%9D%B4%EC%84%9D%EC%9B%90/%EC%BA%A1%EC%B2%98%EC%82%AC%EC%A7%84/path1algo.jpg)-->

## Basic algorithm of path2
<!--
![path2 algo](https://github.com/gwnuysw/AssemblerProject/blob/master/SystemProgramming_Asembler_20141640%EC%9D%B4%EC%84%9D%EC%9B%90/%EC%BA%A1%EC%B2%98%EC%82%AC%EC%A7%84/path2algo.jpg)-->

## License
I captured Algorithm image in 'System Software' written by Leland L.Beck. It is school project, free to use!
