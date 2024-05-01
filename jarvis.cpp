#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Point {
    double x, y;
};

// Calculate the orientation of three points (p, q, r)
int orientation(const Point& p, const Point& q, const Point& r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0; // Collinear
    return (val > 0) ? 1 : 2; // 1: Clockwise, 2: Counterclockwise
}

// Calculate the distance between two points
double distance(const Point& p, const Point& q) {
    return sqrt(pow(q.x - p.x, 2) + pow(q.y - p.y, 2));
}

// Jarvis March algorithm
vector<Point> jarvisMarch(vector<Point>& points) {
    int n = points.size();
    if (n < 3) {
        cout << "Convex hull not possible" << endl;
        return {};
    }

    // Find the leftmost point
    int leftmost = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[leftmost].x) {
            leftmost = i;
        }
    }

    // Initialize the convex hull with the leftmost point
    vector<Point> hull;
    hull.push_back(points[leftmost]);

    // Initialize the current point
    int p = leftmost;

    // Process the remaining points
    while (true) {
        // Find the next point in the convex hull
        int q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            if (orientation(points[p], points[i], points[q]) == 2) {
                q = i;
            }
        }

        // Add the next point to the convex hull
        hull.push_back(points[q]);

        // Update the current point
        p = q;

        // Stop when we reach the starting point again
        if (p == leftmost) break;
    }

    return hull;
}

int main() {
    vector<Point> points = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    vector<Point> hull = jarvisMarch(points);

    cout << "Convex Hull:" << endl;
    for (const Point& p : hull) {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }

    return 0;
}