// 2 линии
// + создать
// + цвет
// + подписать
// + связать с клавой
// + переместить
// + повернуть
// + масштабировать

#include <iostream>
#include <math.h>
#include "graphics.h"
#pragma comment(lib,"graphics.lib")
#define P 3.14

using namespace std;


// класс для точек
class Point {
    public:
        float x; float y;
        void print(Point& point) { 
            cout << point.x << point.y; 
        }
};

// отрисовка линии попиксельно
void line_DDA(float x1, float y1, float x2, float y2, COLORREF cColor, char* nameC, char* nameD) {
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
    outtextxy(x, y, nameC); // начальная точка

    // Основной цикл
    length++;
    while (length--) {
        x += dX;
        y += dY;
        putpixel(roundf(x), roundf(y), cColor);
    }
    outtextxy(x, y, nameD); // конечная точка
}

// отрисовка линии функцией
void drawLine(float x1, float y1, float x2, float y2, COLORREF cColor, char* nameA, char* nameB) {
    setcolor(cColor); // циан 3 или 11
    line(x1, y1, x2, y2);
    outtextxy(x1, y1, nameA);
    outtextxy(x2, y2, nameB);
}


// горизонтальное движение
void moveLinesX(Point& A, Point& B, Point& C, Point& D, float amt, COLORREF col1, char* nameA, char* nameB, COLORREF col2, char* nameC, char* nameD) {
    A.x += amt;
    B.x += amt;
    C.x += amt;
    D.x += amt; 
    cleardevice();
    drawLine(A.x, A.y, B.x, B.y, col1, nameA, nameB);
    line_DDA(C.x, C.y, D.x, D.y, col2, nameC, nameD);
} 

// вертикальное движение
void moveLinesY(Point& A, Point& B, Point& C, Point& D, float amt, COLORREF col1, char* nameA, char* nameB, COLORREF col2, char* nameC, char* nameD) {
    A.y += amt; 
    B.y += amt; 
    C.y += amt; 
    D.y += amt; 
    cleardevice();
    drawLine(A.x, A.y, B.x, B.y, col1, nameA, nameB);
    line_DDA(C.x, C.y, D.x, D.y, col2, nameC, nameD);
}


// поворот одной динии
void rotate(Point& A, Point& B, float ang) { 
    Point tmpA = A, tmpB = B;
    A.x = A.x - B.x; // расстояние от а до б по х
    A.y = A.y - B.y; // по у

    // делает круг вокруг нк, размер норм
    float tmpX = A.x * cos(ang) + A.y * sin(ang);
    float tmpY = -A.x * sin(ang) + A.y * cos(ang);    

    A.x = tmpX + B.x;
    A.y = tmpY + B.y;
}

// поворот двух линий
void rotLines(int u, Point& A, Point& B, Point& C, Point& D, COLORREF col1, char* nameA, char* nameB, COLORREF col2, char* nameC, char* nameD) {
    rotate(A, B, u * 0.05);
    rotate(C, D, u * 0.05);

    moveLinesX(A, B, C, D, 0, col1, nameA, nameB, col2, nameC, nameD); // отрисовка
}


// масштаб одной линии
void scalePoints(Point& A, Point& B, float e) { 
    if ((abs(A.x - B.x) >= 2 && abs(A.y - B.y) >= 2) || e > 1) { // предотвращение сжатия в точку
        float xe = (B.x + A.x) / 2;
        float lx = B.x - A.x;
        lx = lx * e;
        A.x = xe - lx / 2;

        float ye = (B.y + A.y) / 2;
        float ly = B.y - A.y;
        ly = ly * e;
        A.y = ye - ly / 2;
    }
    
}

// масштаб двух линий
void scaleLines(int u, Point& A, Point& B, Point& C, Point& D, COLORREF col1, char* nameA, char* nameB, COLORREF col2, char* nameC, char* nameD) {
    scalePoints(A, B, u);
    scalePoints(C, D, u);

    moveLinesX(A, B, C, D, 0, col1, nameA, nameB, col2, nameC, nameD); // отрисовка
}



int main()
{
    int col1 = 11; // для 1 линии циан 11
    int col2 = 10; // для 2 линии зелёный 2 или 10

    Point A, B, C, D;
    A.x = 20; A.y = 250;
    B.x = 400; B.y = 50;
    C.x = 100; C.y = 50;
    D.x = 500; D.y = 350;

    char *nameA, *nameB, *nameC, *nameD;
    char name_A[2] = "A", name_B[2] = "B", name_C[2] = "C", name_D[2] = "D";
    nameA = name_A; nameB = name_B; nameC = name_C; nameD = name_D;


    initwindow(1400, 700); // создаём консольное окно 1400 на 700

    drawLine(A.x, A.y, B.x, B.y, col1, nameA, nameB); // линия 1
    line_DDA(C.x, C.y, D.x, D.y, col2, nameC, nameD); // линия 2

    // управление
    int i = 1; // условие выхода
    while (i) {
        switch (getch()) {
        case 'w':
            cout << 'w' << endl;
            moveLinesY(A, B, C, D, -10, col1, nameA, nameB, col2, nameC, nameD); // вверх
            break;
        case 'a':
            cout << 'a' << endl;
            moveLinesX(A, B, C, D, -10, col1, nameA, nameB, col2, nameC, nameD); // влево
            break;
        case 's':
            cout << 's' << endl;
            moveLinesY(A, B, C, D, 10, col1, nameA, nameB, col2, nameC, nameD); // вниз
            break;
        case 'd':
            cout << 'd' << endl;
            moveLinesX(A, B, C, D, 10, col1, nameA, nameB, col2, nameC, nameD); // вправо
            break;
        case 'q':
            cout << 'q' << endl;
            rotLines(1, A, B, C, D, col1, nameA, nameB, col2, nameC, nameD); // против часовой
            break;
        case 'e':
            cout << 'e' << endl;
            rotLines(-1, A, B, C, D, col1, nameA, nameB, col2, nameC, nameD); // по часовой
            break;
        case '=':
            cout << '+' << endl;
            scaleLines(2, A, B, C, D, col1, nameA, nameB, col2, nameC, nameD); // увеличение
            break;
        case '-':
            cout << '-' << endl;
            scaleLines(0.9, A, B, C, D, col1, nameA, nameB, col2, nameC, nameD); // уменьшение
            break;
        default:
            cout << "default -> exit" << endl;
            i = 0;
            break;
        }
    }
    

    getch(); // чтение одного символа с клавиатуры
    closegraph(); // освобождает всю память,выделенную под графическую систему, затем восстанавливает экран в режим, который    был   до   вызова   initgraph

    return 0;
}
