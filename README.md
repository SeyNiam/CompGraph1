# CompGraph1
## Лабораторная работа по Компьютерной Графике №1

На экране 2 подписанных цветных отрезка. Один из отрезков задан встроенной функцией, другой отрисован попиксельно.
Отрезки управляются с клавиатуры (по отдельности или синхронно):
- перемещаются во все доступные стороны;
- поворачиваются по и против часовой стрелки, пока не отпущена кнопка;
- масштабируются в "+" и в "-" синхронно по всем осям.

# Формализация
При запуске программы создаётся окно размерами 1400 на 700 функцией initwindow. Для создания и работы с точками используется класс Point, хранящий координаты x и y точки. Функция line_DDA отрисовывает линию по алгоритму DDA-линии. Функция drawLine выводит на экран линию при помощи функции line из библиотеки graphics.h. За перемещение линий отвечают функции moveLinesX, перемещающая их по оси х и moveLinesY, перемещающая их по оси y. Функция rotate поворачивает линию по или против часовой стрелки, а rotLines поворачивает обе линии, вызывая rotate для каждой. Функция scalePoints масштабирует одну линию, а scaleLines обе. По завершении каждой из функций экран отчищается и выводятся новые отредактированные линии. Управление производится при помощи следующих клавиш:
W – перемещение вверх;
A – перемещение влево;
S – перемещение вниз;
D – перемещение вправо;
Q – поворот против часовой стрелки;
E – поворот по часовой стрелке;
- – уменьшение в масштабе;
+ – увеличение в масштабе.
Нажатие любой другой клавиши приводит к завершению программы.
По завершении программы функция closegraph освобождает всю память, выделенную под графическую систему, затем восстанавливает экран в режим, который    был   до   вызова   initwindow.
