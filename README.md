# FormulaParser
Программа реализует калькулятор. С функциями, операциями +, -, *, / и скобками.
Пример выражения: `4/3*pi()*pow(1/2,3)`

Калькулятор:
1. осуществляет парсинг выражения
2. если выражение содержит ошибку, то выводится сообщение об ошибке
если выражение корректно, то калькулятор
1. выводит дерево выражения в псевдографике
2. выводит выражение в функциональном виде
3. вычисляет значение выражения

Ниже пример работы калькулятора для выражения `4/3*pi()*pow(1/2,3)`

Expression tree: 
```
'-- Divide
	|-- Mult
	|   |-- 4
	|   |-- pi
	|   '-- pow
	|       |-- Divide
	|       |   |-- 1
	|       |   '-- 2
	|       '-- 3
	'-- 3
```
Formula in functional style: `Divide(Mult(4.000000,pi(),pow(Divide(1.000000,2.000000),3.000000)),3.000000)`

`4/3*pi()*pow(1/2,3)=0.523598`

-------------------------------------------------------------
При обнаружении ошибки будет выведено сообщение об ошибке.
Если это ошибка парсинга, то будет указано место ошибки:
Пример сообщения об ошибке для ошибочного выражения 2+-3:
```
     Unexpected token '-' at position 3
     2+-3
       ^
```

Грамматика парсера в формулах Бэкуса-науэра:
```
expr ::= [+|-] sum | (expr)
sum ::= mult {+|- mult}
mult ::= item {*|/ item}
item ::= double | func
double ::= intNumber | doubleNumber
func ::= funcName ( expr_list )
expr_list ::= | expr {, expr} 
funcName ::= avg | pow | pi
```
Где:
	<br/>[] - означает, что содержиемое есть, или нет
	<br/>{} - содержимое может повторяться 0 или более раз

Вышеуказанная грамматика поддерживает "унарный минус" и "унарный плюс": -1, -(-5)

Всему этому, и многому другому (структуры, алгоритмы), учили на первом курсе МГУ ВМиК им. М.В. Ломоносова.
