#include <iostream>
#include <vector>
#include <set>
#include <cstdint>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
#include <string>
#include <map>
#include <cmath>


// https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain#C.2B.2B


using namespace std;

typedef double coord_t;         // coordinate type
typedef double coord2_t;  // must be big enough to hold 2*max(|coordinate|)^2

struct Point {
	coord_t x, y;

	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};

// 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
// Returns a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
coord2_t cross(const Point &O, const Point &A, const Point &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<Point> convex_hull(vector<Point> P)
{
	int n = P.size(), k = 0;
	if (n == 1) return P;
	vector<Point> H(2*n);

	// Sort points lexicographically
	sort(P.begin(), P.end());

	// Build lower hull
	for (int i = 0; i < n; ++i) {
		while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	// Build upper hull
	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	H.resize(k-1);
	return H;
}





int main()
{
    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;

    // Point points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
    //                   {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    // int n = sizeof(points)/sizeof(points[0]);
    // convexHull(points, n);
    // return 0;

    for (int testCase=1; testCase<=t; ++testCase)
    {
        std::cout << "Case #" << testCase << ": ";
        std::cout << "\n";

        int n;
        std::cin >> n;

        std::vector<Point> points;
        for (int i=0; i<n; ++i)
        {
            double x, y, z, d;
            std::cin >> x;
            std::cin >> y;
            std::cin >> z; // not needed
            std::cin >> d; // not needed
            points.push_back({x, y});
        }


        std::vector<Point> result = convex_hull(points);

        std::sort(result.begin(), result.end(), [](Point a, Point b) {
            if (a.x < b.x)
                return true;
            else if (a.x == b.x)
                if (a.y < b.y)
                    return true;
                else
                    return false;
            else
                return false;
        });

        std::cout << result.size() << "\n";
        for (const auto ppp : result)
        {
            std::cout << ppp.x << " " << ppp.y << "\n";
        }

        result.clear();
    }

    return 0;
}
