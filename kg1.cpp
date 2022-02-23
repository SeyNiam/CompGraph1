// 2 линии
// + создать
// + цвет
// - подписать
// - связать с клавой
// - переместить
// - повернуть
// - масштабировать

#include <iostream>
#include <math.h>
#include "graphics.h"
#pragma comment(lib,"graphics.lib")

using namespace std;

// функция отрисовки линии попиксельно
//#define roundf(x) floor((x) + 0,5f)
void line_DDA(float x1, float y1, float x2, float y2, COLORREF cColor) {
    // Целочисленные значения координат начала и конца отрезка, округлённые до ближайшего целого
    int iX1 = roundf(x1);
    int iY1 = roundf(y1);
    int iX2 = roundf(x2);
    int iY2 = roundf(y2);

    // Длина и высота линии
    int deltaX = abs(iX1 - iX2);
    int deltaY = abs(iY1 - iY2);

    // Считаем минимальное количество итераций, необходимое  для отрисовки отрезка
    // Выбирая максимум из длины и высоты линии, обеспечиваем связность линии
    int length = max(deltaX, deltaY);

    // особый случай, на экране закрашивается ровно один пиксель
    if (length == 0) {
        putpixel(iX1, iY1, cColor);
        return;
    }
    // Вычисляем приращения на каждом шаге по осям абсцисс и ординат
    double dX = (x2 - x1) / length;
    double dY = (y2 - y1) / length;

    // Начальные значения
    double x = x1;
    double y = y1;

    // Основной цикл
    length++;
    while (length--) {
        x += dX;
        y += dY;
        putpixel(roundf(x), roundf(y), cColor);
    }

}



int main()
{
    initwindow(1400, 700); // создаём консольное окно 500 на 500

    //setcolor(14); // жёлтый 14
    //line(50, 100, 100, 300);

    // линия 1
    setcolor(11); // циан 3 или 11
    line(20, 250, 400, 50);

    // линия 2
    line_DDA(100, 50, 500, 350, 10); // зелёный 2 или 10





    getch(); // чтение одного символа с клавиатуры
    closegraph(); // освобождает всю память,выделенную под графическую систему, затем восстанавливает экран в режим, который    был   до   вызова   initgraph

    return 0;
}
