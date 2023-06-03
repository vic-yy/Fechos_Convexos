#include <iostream>
#include "../include/stack.h"
#include "../include/vector.h"

using namespace std;

struct Point {
    int x, y;
};

Point p0;

Point nextToTop(stack<Point>& S) {
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

void swap(Point& p1, Point& p2) {
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

int distSq(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0)
        return 0;
    return (val > 0) ? 1 : 2;
}

int compare(const void* vp1, const void* vp2) {
    Point* p1 = (Point*)vp1;
    Point* p2 = (Point*)vp2;

    // Find orientation
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;

    return (o == 2) ? -1 : 1;
}

void merge(Point arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    Point L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i].x <= R[j].x) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Point arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void convexHull(Point points[], int n) {
    // Find the bottommost point
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;

        // Pick the bottom-most or choose the left
        // most point in case of tie
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x))
            ymin = points[i].y, min = i;
    }

    // Place the bottom-most point at the first position
    swap(points[0], points[min]);

    // Sort n-1 points with respect to the first point.
    // A point p1 comes before p2 in sorted output if p2
    // has a larger polar angle (in counterclockwise
    // direction) than p1
    p0 = points[0];
    mergeSort(points, 1, n - 1);

    // If two or more points make the same angle with p0,
    // remove all but the one that is farthest from p0
    // Remember that, in the above sorting, our criteria was
    // to keep the farthest point at the end when more than
    // one points have the same angle.
    int m = 1; // Initialize size of modified array
    for (int i = 1; i < n; i++) {
        // Keep removing i while the angle of i and i+1 is the same
        // with respect to p0
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++;

        points[m] = points[i];
        m++; // Update the size of the modified array
    }

    // If the modified array of points has less than 3 points,
    // convex hull is not possible
    if (m < 3)
        return;

    // Create an empty stack and push the first three points to it.
    stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    // Process the remaining n-3 points
    for (int i = 3; i < m; i++) {
        // Keep removing the top while the angle formed by
        // points next-to-top, top, and points[i] makes
        // a non-left turn
        while (S.size() > 1 && orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop();
        S.push(points[i]);
    }

    // Now the stack has the output points, print the contents of the stack
    while (!S.empty()) {
        Point p = S.top();
        cout << "(" << p.x << ", " << p.y << ")" << endl;
        S.pop();
    }
}

int main() {
    Vector<Point> points;
    int a, b;

    while (cin >> a >> b) {
        Point p;
        p.x = a;
        p.y = b;
        points.push_back(p);
    }

    Point pontos[points.size()];

    for (int i = 0; i < points.size(); i++) {
        pontos[i] = points[i];
    }

    mergeSort(pontos, 0, points.size() - 1);
    convexHull(pontos, points.size());

    return 0;
}
