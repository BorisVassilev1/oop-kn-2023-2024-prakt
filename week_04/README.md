# 4: static, списъци

За всички следващи задачи напишете и main-функция която показва правилната работа на дефинираните класове/функции.

## 1) 
Напишете клас Student, който има член-данни име (низ с дължина до 100 символа) и факултетен номер (цяло положително число). При създаване на инстанция на класа Student, името да се подава в конструктура, а факултетния номер да се създава автоматично: първият фак. номер е 0, вторият е 1 и тн. Искаме всеки следващ студент да получава различен факултетен номер.
### * (творческа задача)
Нека факултетния номер е низ с дължина 10 символа, първата цифра да е "верифицираща", т.е. да се получава от другите чрез някакъв алгоритъм, следващите символи да са "MI08", а последните 5 цифри започват от "00000" и се инкрементират.

## 2)
Напишете клас Counted, и статична функция `size_t Counted::getCount()`, която връща броя обекти от тип Counted, които съществуват в даден момент.

## 3) 
Напишете шаблон на клас UncopiableArray, чиито размер се задава в конструктура. Освен това:
- да има метод, която достъпва `i`-тия елемент на масива
- да има метод, която връща размера на масива
- обекти от този тип да не могат да се копират.

Пример: 
```cpp
UncopiableArray a(10), b(10);
for(size_t i = 0; i < a.size(); ++i) { a.get(i) = i;}
a = b // -> невалидно
UncopiableArray c(a); // -> невалидно
```

## 4) 
Напишете на клас Vector, който представя масив от цели числа, чиито размер по начало е `0`. Да се реализира
- да има метод, която достъпва `i`-тия елемент на масива
- да има метод, която връща размера на масива
- да има метод, която добавя елемент в края на масива
- да има метод, която приема указател към масив и размер, като добавя съответните елементи в края на масива.
- да се реализира конструктор, който приема размер `s` и константа `t`, и запълва масива с `s` на брой стойности `t`. 
- да се реализира метод, който копира някаква подредица от масива в нов Vector (от индекс `i` до индекс `j`)
- да се реализира метод, който сортира масива спрямо подадена функция $f: int \times int -> \{0, 1\}$, която да играя ролята на сравнение $<$.

## 5)
Напишете шаблон на клас Generator, който приема ламбда-функция $f: T \rightarrow T$ и начална стойност от тип $Т$. Реализирайте метод `next()`, който връща 'следващия' елемент от редицата, прилагаща последователно $f$. Т.е. Искаме следното поведение:
```cpp
Generator<int> nats(0, [](int x) -> int { return x + 1; });
std::cout << nats.next() << std::endl;	 // 0
std::cout << nats.next() << std::endl;	 // 1
std::cout << nats.next() << std::endl;	 // 2

Generator<double> rand(0.5, [](double x) -> double {
	x = std::abs(std::sin(x * 123872.9898) * 43758.5453 + 1.2315);
	return x - (int)x;
});

for(int i = 0; i < 100; ++i) {
	std::cout << rand.next() << std::endl; // псевдо-случайни числа
}
```

## 6) Бонус
Използвайте типа Vector за да реализирате функция `map`, която приема масив, както и функция, която да приложи върху всеки от елементите на масива. Да се връща нов масив (не непременно от същия тип като изходния), който съдържа резултатите след прилагането на функцията.

Пример: 
```cpp
Vector<int> arr(10);
for(std::size_t i = 0; i < arr.size(); ++i) {
	arr.get(i) = i;
}
Vector<float> res = map<int, float>(arr, [](int x) -> float {return std::sqrt(x);});
// 0 1 1.41421 1.73205 2 2.23607 2.44949 2.64575 2.82843 3 
```
Ако изпращате тази задача като домашно, отделете функцията `map` в отделен хедър файл. Предайте също и своята имплементация на Vector. Помислете и защо не можем тук да ползваме UncopiableArray?
