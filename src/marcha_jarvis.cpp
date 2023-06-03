#include <iostream>
#include <vector>

struct Point {
    int x, y;

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

void jarvisMarch(std::vector<Point>& points) {
    int n = points.size();
    if (n < 3)
        return;

    std::vector<Point> convexHull;

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
    for (const auto& point : convexHull) {
        std::cout  << point.x << "; " << point.y << std::endl;
    }
}

int main() {
    int numPoints;
    std::cout << "Digite o número de pontos: ";
    std::cin >> numPoints;

    std::vector<Point> points;
    for (int i = 0; i < numPoints; i++) {
        int x, y;
        // std::cout << "Digite as coordenadas x e y do ponto " << i + 1 << ": ";
        std::cin >> x >> y;
        points.push_back(Point(x, y));
    }

    jarvisMarch(points);

    return 0;
}
