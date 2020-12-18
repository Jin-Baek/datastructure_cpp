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

    // priority_queue ��� ( <�Ÿ�, ���� ���> )
    priority_queue<pair<int, int> > q;
    q.push(make_pair(0, start));

    // �Ÿ� �� ��� vector
    vector<int> distSum(Node, INFINITE);
    distSum[start] = 0;
    
    while (!q.empty()) {
        // ���ͽ�Ʈ�� �˰��� : ���� ���� ����ġ ����
        // �켱 ���� ť : ū �� ���� -> (-) ���̱� 
        int distance = -q.top().first;
        int from = q.top().second;
        q.pop();

        if (distSum[from] < distance) {
            continue;
        }else{
            for (int i = 0; i < graph[from].size(); i++) {
                int to = graph[from][i].first;
                int next_dist = graph[from][i].second;
                // �Ÿ� ���� -> from�� ���� ���� �ִ� ��忡�� ����Ǵ� ���� ������ �� ����� ������� ��ȣ�� ť�ȿ� ���� �ְԵǰ� 
                // �̰� ������ ������ distSum �ʱⰪ�� INF�� �� �����صξ��� ������. �׷��� ť�� �� �ڿ� �ٽ� while������ ���ٰ� ���� �տ� �ִ°Ÿ� 
                //pop�ϸ� (-)�� �پ��� ������ ������ ���� ���� ������ �������� ���ͽ�Ʈ�� ������� ������ ������ ��尡 ���ų� �ϸ� if�� �ɷ��� 
                // continue�� �ϰԵǰ� q���� �������� ���� ���� pop�ؿ��Եȴ�. �׸��� �� �� ���� ������ �� ��� ���� �� cost�� �� ���� ���� �Ʒ� if ���� ���� 
                // �ɷ����� �ּ� �Ÿ��� q�� �ְԵȴ�.
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

    cout << "[ ��� �ֹ� ��(Vertex) , ��� ������ ���� ��(Edge) ] : ";

    cin >> Node >> Edge;

    graph->resize(Node + 1);

    if (Node > MAX_Node) {
        cout << "����� �� ���� 10�� �̻� �Ұ��� �մϴ�";
    }
    cout << "\n-------------------------------";
    cout << "\n| 0 : ����  �� �� : ��� ���� |\n";
    cout << "-------------------------------\n\n";

    for (int i = 0; i < Edge; i++) {
        cout<<"[��� ���� ����] from to :";
        int from, to, dis, tmp;
        cin >> from >> to;

        dis = random(rd);
        tmp = dis;
        dis = dis - tmp % 10;

        cout << from << " �� " << to << " �Ÿ�: " << dis << "m \n\n";

        graph[from].push_back(make_pair(to, dis));
        graph[to].push_back(make_pair(from, dis));
    }

    cout << "=== ���� ���� �Ÿ��� ���� ��޺� ����===\n\n";
    vector<int> distSum = dijkstra(0, Node);

    for (int i = 1; i < Node; i++) {
        int cost;

        if (distSum[i] < 500) {
            cout << i << "�� ����� : " << distSum[i] << " m / " << "Free" << "\n";
        }
        else if (distSum[i] > 3000) {
            cout << i << "�� ����� : " << distSum[i] << " m / " << "��� �Ұ� ����" << "\n";
        }
        else {
            cost = distSum[i] * 250 / 100;
            cout << i << "�� ����� : " << distSum[i] << " m / " << cost - (cost % 100) << "�� \n";
        }
    }
    return 0;
}