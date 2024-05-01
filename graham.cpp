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

// Compare two points based on their polar angle
bool compare(const Point& p, const Point& q) {
    int o = orientation({0, 0}, p, q);
    if (o == 0) {
        return distance({0, 0}, p) < distance({0, 0}, q);
    }
    return o == 2;
}

// Graham Scan algorithm
vector<Point> grahamScan(vector<Point>& points) {
    int n = points.size();
    if (n < 3) {
        cout << "Convex hull not possible" << endl;
        return {};
    }

    // Find the bottom-most point
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;
        // Check if the current point is below the bottom-most point or if it is at the same level but to the left
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x)) {
            ymin = points[i].y;
            min = i;
        }
    }

    // Swap the bottom-most point with the first point
    swap(points[0], points[min]);

    // Sort points based on polar angle
    sort(points.begin() + 1, points.end(), compare);

    // Initialize the convex hull with the first two points
    vector<Point> hull = {points[0], points[1]};

    // Process the remaining points
    for (int i = 2; i < n; i++) {
        while (hull.size() > 1 && orientation(hull[hull.size() - 2], hull.back(), points[i]) != 2) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    return hull;
}

int main() {
    vector<Point> points = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    vector<Point> hull = grahamScan(points);

    cout << "Convex Hull:" << endl;
    for (const Point& p : hull) {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }

    return 0;
}