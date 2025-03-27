#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct Point
{
    int x, y;
};

// Функция для нахождения НОД
int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

// Функция для вычисления максимального количества точек на одной прямой
int maxPointsOnLine(const vector<Point>& points) 
{
    if (points.size() < 2) 
        return points.size();

    int maxPoints = 0;

    for (int i = 0; i < points.size(); ++i) 
    {
        map<pair<int, int>, int> slopes;
        int duplicate = 1;
        int vertical = 0;

        for (int j = 0; j < points.size(); ++j) 
        {
            if (i == j)
                continue;

            int dx = points[j].x - points[i].x;
            int dy = points[j].y - points[i].y;

            if (dx == 0 && dy == 0) 
            {
                duplicate++;
            }
            else if (dx == 0) 
            {
                vertical++;
            }
            else
            {
                int g = gcd(dx, dy);
                dx /= g;
                dy /= g;

                if (dx < 0) 
                {
                    dx = -dx;
                    dy = -dy;
                }

                slopes[{dy, dx}]++;
            }
        }

        int currentMax = vertical;
        for (const auto& slope : slopes) 
        {
            currentMax = max(currentMax, slope.second);
        }

        maxPoints = max(maxPoints, currentMax + duplicate);
    }

    return maxPoints;
}

int main() 
{
    setlocale(LC_ALL, "rus");

    int n;
    cout << "Введите количество точек: ";
    cin >> n;

    vector<Point> points(n);
    cout << "Введите координаты точек (x и y):\n";
    for (int i = 0; i < n; ++i)
    {
        cin >> points[i].x >> points[i].y;
    }

    cout << "Максимальное количество точек на одной прямой: " << maxPointsOnLine(points) << "\n";

    return 0;
}
