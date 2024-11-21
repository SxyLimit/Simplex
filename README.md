# 单纯形

## 算法流程图

```mermaid
graph TD
	A[开始] --> B[初始化和输入]
	B --> C[每个约束条件添加变量实现二阶段法]
	C --> H[将检验系数进行消元]
	C --> D[单纯形法计算，得到基本可行解]
	D --> E[判断是否有基本可行解]
	E -- 是 --> I[将检验系数进行消元]
	I --> F[带入目标行继续用单纯形计算]
	E -- 否 --> G[输出无解后推出程序]
```
```mermaid
graph TD
	A[计算单纯形] --> B[利用检验数判断是否为最优解]
	B -- 是 --> F[判断解是否唯一]
	F -- 是 --> G[消元解出唯一解并输出]
	F -- 否 --> H[计算基础解系并输出]
	B -- 否 --> C[寻找新的入基变量和离基变量]
	C -- 没有找到 --> D[输出无解并退出]
	C -- 找到 --> E[修改基变量并通过高斯消元计算出新的系数]
	E --> I[输出单纯形表]
	I --> B
```

## 如何使用

### 输入格式

输入文件 `input.txt` 第一行必须包含

将可执行文件与 `input.txt` 放在同一文件夹下，并运行可执行文件，会生成一个 `output.txt` 文件，计算单纯形的过程和结果会输出在其中。

## 有待实现的

优化输入格式为
```
n
a[1][1]*x1+a[1][2]*x2+...+a[1][n]*xn<=b[1]
...
.
.
```
其中 `a[1][1],b[1]` 等数可以以分数 `a/b` 或小数 `a.b` 的形式输入。

`x1` 等变量可以自定义变量名（以大小写字母或下划线开头，仅能包含大小写字母、下划线和数字），但是有一些变量名为**关键词**不能使用，如 add+数字 等。

输入可以为等式或不等式（`=`,`<=`,`>=`）会通过添加变量转化为标准型。

目前仅支持计算出线性规划的最优解，不支持输出最优解的取等条件。当解唯一时输出最优解，当解不唯一时输出最优解的线性表示。
