#pragma warning(disable:4996)
#include <iostream>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <random>

using namespace std;

#define INFINITE 1000001
#define MAX_Node 10

std::random_device rd;
std::uniform_int_distribution<int> random(50, 1500);

vector<pair<int, int> > graph[MAX_Node];

vector<int> dijkstra(int start, int Node) {

    // priority_queue 사용 ( <거리, 도착 노드> )
    priority_queue<pair<int, int> > q;
    q.push(make_pair(0, start));

    // 거리 합 기록 vector
    vector<int> distSum(Node, INFINITE);
    distSum[start] = 0;
    
    while (!q.empty()) {
        // 다익스트라 알고리즘 : 가장 작은 가중치 먼저
        // 우선 순위 큐 : 큰 값 먼저 -> (-) 붙이기 
        int distance = -q.top().first;
        int from = q.top().second;
        q.pop();

        if (distSum[from] < distance) {
            continue;
        }else{
            for (int i = 0; i < graph[from].size(); i++) {
                int to = graph[from][i].first;
                int next_dist = graph[from][i].second;
                // 거리 갱신 -> from을 통해 원래 있던 노드에서 연결되는 여러 노드까지 각 값들과 도착노드 번호를 큐안에 집어 넣게되고 
                // 이게 가능한 이유는 distSum 초기값을 INF로 다 설정해두었기 때문임. 그래서 큐에 들어간 뒤에 다시 while문으로 갔다가 가장 앞에 있는거를 
                //pop하면 (-)가 붙었기 때문에 실제로 가장 작은 값부터 가져오는 다익스트라 성질대로 되지만 다음에 노드가 없거나 하면 if에 걸려서 
                // continue를 하게되고 q에서 다음으로 작은 수를 pop해오게된다. 그리고 이 밑 식은 나뉘는 두 길로 갔을 때 cost가 더 작은 쪽을 아래 if 문을 통해 
                // 걸러내서 최소 거리를 q에 넣게된다.
                if (distSum[from]+next_dist < distSum[to]) {
                    distSum[to] = distSum[from]+next_dist;
                    q.push(make_pair(-distSum[to], to));
                }
            }
        }
    }
    return distSum;
}

int main()
{
    int Node, Edge;

    cout << "[ 배달 주문 수(Vertex) , 사용 가능한 도로 수(Edge) ] : ";

    cin >> Node >> Edge;

    graph->resize(Node + 1);

    if (Node > MAX_Node) {
        cout << "배달은 한 번에 10곳 이상 불가능 합니다";
    }
    cout << "\n-------------------------------";
    cout << "\n| 0 : 매장  그 외 : 배달 지역 |\n";
    cout << "-------------------------------\n\n";

    for (int i = 0; i < Edge; i++) {
        cout<<"[사용 가능 도로] from to :";
        int from, to, dis, tmp;
        cin >> from >> to;

        dis = random(rd);
        tmp = dis;
        dis = dis - tmp % 10;

        cout << from << " ↔ " << to << " 거리: " << dis << "m \n\n";

        graph[from].push_back(make_pair(to, dis));
        graph[to].push_back(make_pair(from, dis));
    }

    cout << "=== 매장 기준 거리에 따른 배달비 측정===\n\n";
    vector<int> distSum = dijkstra(0, Node);

    for (int i = 1; i < Node; i++) {
        int cost;

        if (distSum[i] < 500) {
            cout << i << "번 배달지 : " << distSum[i] << " m / " << "Free" << "\n";
        }
        else if (distSum[i] > 3000) {
            cout << i << "번 배달지 : " << distSum[i] << " m / " << "배송 불가 지역" << "\n";
        }
        else {
            cost = distSum[i] * 250 / 100;
            cout << i << "번 배달지 : " << distSum[i] << " m / " << cost - (cost % 100) << "원 \n";
        }
    }
    return 0;
}