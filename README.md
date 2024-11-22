# 单纯形

## 算法流程图

```mermaid
flowchart TD
	A(开始) --> B[初始化和输入]
	B --> C[每个约束条件添加变量实现二阶段法]
	C --> H[将检验系数进行消元]
	H --> D[单纯形法计算得到基本可行解]
	D --> E{判断是否有基本可行解}
	E -->|是| I[将检验系数进行消元]
	I --> F[带入目标行继续用单纯形计算]
	E -->|否| G[输出无解后推出程序]
```
```mermaid
flowchart TD
	A(计算单纯形) --> B{利用检验数判断是否为最优解}
	B -->|是| F{判断解是否唯一}
	F -->|是| G[输出唯一解]
	F -->|否| H[输出说明有无穷解并输出其中一组解]
	B -->|否| C{寻找新的入基变量和离基变量}
	C -->|没有找到| D[输出无解并退出]
	C -->|找到| E[修改基变量并通过高斯消元计算出新的系数]
	E --> I[输出单纯形表]
	I --> B
```

## 如何使用

### 环境配置

运行前需要确保电脑上已经有 g++ 环境。若没有环境可以在 [Windows 版本下载链接](https://github.com/niXman/mingw-builds-binaries/releases/download/14.2.0-rt_v12-rev0/x86_64-14.2.0-release-posix-seh-ucrt-rt_v12-rev0.7z)，其他系统请在 [下载链接](https://github.com/niXman/mingw-builds-binaries/releases) 中选择合适版本下载并添加环境变量后运行。

### 输入格式

输入文件 `input.txt` 第一行必须包含一个整数 $n$

接下来 $n$ 行为 $n$ 个约束条件，每一行的格式格式均为

```
a1*x1+a2*x2+...+am*xm=b
```

其中 `a1,a2,...,am,b` 可以用分数 `a/b` 或者小数 `a.b` 输入，`*` 可以省略，`+` 也可以替换为减号，`x1,x2,...,xm` 为变量名，格式为以下划线或大小写字母开头，仅包含下划线，大小写字母和数字构成的字符串，且不要使用 `y`+ 数字和 `add`+ 数字，`=` 可以换成 `<=` 和 `>=`。

接下来一行为需要最小化的函数，输入格式为

```
a1*x1+a2*x2+...+am*xm
```

具体限制同上

以下给出一个正确输入的例子：
```
3
x1+4.5/3.000xxx_2+0.5*xxx_2<=5
-x1 -x3 <= -3
2/1*x1 - 233/233xxx_2+x3=2
-2.0*x1 + xxx_2
```

输入后，将 `run.bat` 与 `input.txt` 放在同一文件夹下，并运行 `run.bat`，会生成一个 `output.txt` 文件，计算单纯形的过程和结果会输出在其中。

入上例子在 `output.txt` 中的输出为：
```
    |x1|x3|xxx_2|y0|y1|add1|add2|add3|RHS
----+--+--+-----+--+--+----+----+----+---
add1|1 |0 |2    |1 |0 |1   |0   |0   |5
----+--+--+-----+--+--+----+----+----+---
add2|1 |1 |0    |0 |-1|0   |1   |0   |3
----+--+--+-----+--+--+----+----+----+---
add3|2 |1 |-1   |0 |0 |0   |0   |1   |2
----+--+--+-----+--+--+----+----+----+---
g   |0 |0 |0    |0 |0 |-1  |-1  |-1  |0

    |x1|x3|xxx_2|y0|y1|add1|add2|add3|RHS
----+--+--+-----+--+--+----+----+----+---
add1|1 |0 |2    |1 |0 |1   |0   |0   |5
----+--+--+-----+--+--+----+----+----+---
add2|1 |1 |0    |0 |-1|0   |1   |0   |3
----+--+--+-----+--+--+----+----+----+---
add3|2 |1 |-1   |0 |0 |0   |0   |1   |2
----+--+--+-----+--+--+----+----+----+---
g   |4 |2 |1    |1 |-1|0   |0   |0   |10

add1->xxx_2
    |x1|x3  |xxx_2|y0|y1|add1|add2|add3|RHS
----+--+----+-----+--+--+----+----+----+---
add1|0 |-1/2|5/2  |1 |0 |1   |0   |-1/2|4
----+--+----+-----+--+--+----+----+----+---
add2|0 |1/2 |1/2  |0 |-1|0   |1   |-1/2|2
----+--+----+-----+--+--+----+----+----+---
x1  |1 |1/2 |-1/2 |0 |0 |0   |0   |1/2 |1
----+--+----+-----+--+--+----+----+----+---
g   |0 |0   |3    |1 |-1|0   |0   |-2  |6

x1->x1
     |x1|x3  |xxx_2|y0  |y1|add1|add2|add3|RHS
-----+--+----+-----+----+--+----+----+----+---
xxx_2|0 |-1/5|1    |2/5 |0 |2/5 |0   |-1/5|8/5
-----+--+----+-----+----+--+----+----+----+---
add2 |0 |3/5 |0    |-1/5|-1|-1/5|1   |-2/5|6/5
-----+--+----+-----+----+--+----+----+----+---
x1   |1 |2/5 |0    |1/5 |0 |1/5 |0   |2/5 |9/5
-----+--+----+-----+----+--+----+----+----+---
g    |0 |3/5 |0    |-1/5|-1|-6/5|0   |-7/5|6/5

add2->x3
     |x1|x3|xxx_2|y0  |y1  |add1|add2|add3|RHS
-----+--+--+-----+----+----+----+----+----+---
xxx_2|0 |0 |1    |1/3 |-1/3|1/3 |1/3 |-1/3|2
-----+--+--+-----+----+----+----+----+----+---
x3   |0 |1 |0    |-1/3|-5/3|-1/3|5/3 |-2/3|2
-----+--+--+-----+----+----+----+----+----+---
x1   |1 |0 |0    |1/3 |2/3 |1/3 |-2/3|2/3 |1
-----+--+--+-----+----+----+----+----+----+---
g    |0 |0 |0    |0   |0   |-1  |-1  |-1  |0

min:0
x1=1
x3=2
xxx_2=2
y0=0
y1=0
add1=0
add2=0
add3=0
     |x1|x3|xxx_2|y0  |y1  |RHS
-----+--+--+-----+----+----+---
xxx_2|0 |0 |1    |1/3 |-1/3|2
-----+--+--+-----+----+----+---
x3   |0 |1 |0    |-1/3|-5/3|2
-----+--+--+-----+----+----+---
x1   |1 |0 |0    |1/3 |2/3 |1
-----+--+--+-----+----+----+---
z    |0 |0 |0    |-1/3|-5/3|0

min:0
x1=1
x3=2
xxx_2=2
y0=0
y1=0
```

即最后得到当 $x_1=1,x_3=2,xxx_2=2,y_0=0,y_1=0$  时取得最小值 $\min -2x_1+xxx_2=0$。

更多的输入输出例子在 `Examples` 文件夹中。

## 有待实现的

当解不唯一时输出最优解的线性表示。（解空间为一个凸集，可能不存在多项式个数内的线性表示）

目前只有 $\mathrm{Dantzig}$ 规则的迭代方式，也只有以分数存储的方式。在计算过程中可能会陷入循环或者分数过大而导致错误。可能会加入大 $M$ 法、字典序法等迭代方式和小数模式等。
