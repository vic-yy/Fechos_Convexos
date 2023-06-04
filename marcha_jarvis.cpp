#include <iostream>
// #include <vector>
#include "../include/vector.h"
using namespace std;

struct Point {
    int x, y;

    Point() : x(0), y(0) {}  // Default constructor

    Point(int xCoord, int yCoord) : x(xCoord), y(yCoord) {}
};


// Função para encontrar o próximo ponto na envoltória convexa
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0)
        return 0;  // Colinear
    else if (val > 0)
        return 1;  // Sentido horário
    else
        return 2;  // Sentido anti-horário
}

void jarvisMarch(Vector<Point>& points) {
    int n = points.getSize();
    if (n < 3)
        return;

    Vector<Point> convexHull;

    // Encontra o ponto mais à esquerda
    int leftmost = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[leftmost].x)
            leftmost = i;
    }

    int p = leftmost, q;
    do {
        convexHull.push_back(points[p]);
        q = (p + 1) % n;

        for (int i = 0; i < n; i++) {
            // Verifica se i é mais à esquerda que q
            if (orientation(points[p], points[i], points[q]) == 2)
                q = i;
        }

        p = q;
    } while (p != leftmost);

    // Imprime os pontos na envoltória convexa
    // std::cout << "Envoltória convexa:" << std::endl;
    for (int i = 0; i < convexHull.getSize(); i++) {
        std::cout  << points[i].x << "; " << points[i].y << std::endl;
    }
}

int main() {
    Vector<Point>points;
    int a, b;


    while(cin >> a >> b){
        Point p(a,b);
        points.push_back(p);
    }

    jarvisMarch(points);

    return 0;
}
