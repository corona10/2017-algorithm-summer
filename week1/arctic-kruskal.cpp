/**
 Summer Algorithm study
 Problems: https://algospot.com/judge/problem/read/ARCTIC
 Solution: Using kruskal algorithm
 Keywords: Kruskal algorithm, Union-find algorithm
**/
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

struct Point {
    double x;
    double y;
};

struct Edge {
    int from;
    int to;
    double distance;
};

// 유클리디언 거리 계산
double getDistance(const Point& p1, const Point& p2);
// 우선순위 큐를 위한 엣지가 거리 비교
bool EdgeCompare(const Edge& e1, const Edge& e2);
// Find
int find(int* parent, int i);
// Union
void Union(int* parent, int& x, int& y);

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) {
        std::vector<Point> point_vec;
        std::priority_queue<Edge, std::vector<Edge>, std::function<bool(Edge, Edge)>> pq(EdgeCompare);
        int points;
        cin >> points;
        
        // 각 관측소 입력 받기
        for(int j = 0; j < points; j++) {
            Point p;
            cin >> p.x >> p.y;
            point_vec.push_back(p);
        }
    
        size_t numberOfPoint = point_vec.size();        
        // 모든 관측소와 그래프 연결하기.(N^2 Edge 그래프 생성)
        for(int j = 0; j < numberOfPoint; j++){
            for(int k = 0; k < numberOfPoint; k++) {
                if ( j == k )
                    continue;
                Edge e;
                e.from = j;
                e.to = k;
                e.distance = getDistance(point_vec[j], point_vec[k]);
                pq.push(e);
            }
        }
        
        int* parent = new int[numberOfPoint];
        memset(parent, -1, sizeof(int)*numberOfPoint);
        double max_distance = 0;
        vector<double> distances;
        
        // 크루스칼 알고리즘의 핵심, 정점의 갯수 -1 개의 갯수의
        // 경로를 찾을 때까지 검색 이 때 사이클이 생성되면 안된다.
        // 사이클 검출은 union-find 알고리즘을 사용한다.
        while(distances.size() != (numberOfPoint-1)) {
            Edge e = pq.top(); pq.pop();
            int from_parent = find(parent, e.from);
            int to_parent = find(parent, e.to);
            
            // 부모가 같다는 것은 사이클을 성립한다는 것이다.
            // 그러므로 스킵한다.
            if(from_parent == to_parent) {
                continue;
            }
            
            // 사이클이 아니면 부모를 업데이트 해주고,
            // 현재 거리랑 최대 거리랑 비교해서 업데이트!
            Union(parent, from_parent, to_parent);
            distances.push_back(e.distance);
            if(max_distance < e.distance) {
                max_distance = e.distance;
            }

        }
        
        cout<<fixed;
        cout.precision(2);
        cout<<max_distance<<endl;
        delete [] parent;
    }
    return 0;
}

double getDistance(const Point& p1, const Point& p2) {
    double dis = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    return dis;
}

bool EdgeCompare(const Edge& e1, const Edge& e2) {
    return e1.distance > e2.distance;
}

int find(int* parent, int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

void Union(int* parent, int& x, int& y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}
