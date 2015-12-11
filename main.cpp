#include <iostream>
#include "stdlib.h"
using namespace std;
class VertexNode {
public:
    int num;
    int indegree;
    int outdegree;
    int neiboIndex;
    VertexNode* neibo;
    VertexNode() {
        num = 0;
        indegree = 0;
        outdegree = 0;
        neiboIndex = 0;
        neibo = NULL;
    }
    ~VertexNode() {
        if (outdegree) {
            free(neibo);
        }
    }
};
typedef VertexNode* pNode;
VertexNode v[1000001];
void createGraph(const int &n, const int&m) {
    int* eBegin = new int[m];
    int* eEnd = new int[m];
    for (int i = 0; i < m; i++)
    {
        cin >> eBegin[i] >> eEnd[i];
        int start = eBegin[i];
        int end = eEnd[i];
        if (!v[start].num) {   //给V中的节点赋值，把每边端点的数字赋值给start，end下同
            v[start].num = start;
        }
        if (!v[end].num) {
            v[end].num = end;
        }
        v[start].outdegree++; //start出度加1
        v[end].indegree++; //end入度加1
    }
    for (int i = 1; i <=n; i++)
    {
        int neiboNum = v[i].outdegree;//为每一个节点开neibo数组
        if (neiboNum) {
            v[i].neibo = pNode(malloc(neiboNum * sizeof(VertexNode)));
        }
    }
    for (int i = 0; i < m; i++)
    {
        int start = eBegin[i];//对于每一条边，把边上的end节点添加到start的neibo上
        int end = eEnd[i];
        pNode p = v[start].neibo;
        p[v[start].neiboIndex] = v[end];
        v[start].neiboIndex++;
    }
    delete eBegin, eEnd;
}
class Stack
{
public:
    Stack(int n)
    {
        top = 0;
        data = new int[n];
    }
    ~Stack()
    {
        delete[]data;
    }
    void push(const int& value)
    {
        data[top++] = value;
    }
    int& pop()
    {
        return data[--top];
    }
    bool isEmpty()
    {
        return top == 0;
    }

protected:
private:
    int* data;
    int top;
};
int topoSort(Stack &s, const int &n) {
    int max = 1;
    int* villages = new int[n + 1];
    for (int i = 0; i <=n; i++)
    {
        villages[i] = 1;   //记录每个村子对应的最长路径长度，默认都为1
    }
    for (int i = 1; i <=n; i++)
    {
        if (v[i].indegree == 0) {
            s.push(i);  //把入度等于0的点入栈
        }
    }
    while (!s.isEmpty())
    {
        int node = s.pop();   //取一个入度为0的node
        for (int i = 0; i < v[node].outdegree; i++)  //遍历node所有的邻居
        {
            pNode p = &(v[node].neibo[i]);
            if (p)
            {
                if (villages[node]+1>villages[p->num])//模拟向下走一步的过程
                {
                    villages[p->num] = villages[node] + 1;
                }
                if (max<villages[p->num])  //如果最大则更新max
                {
                    max = villages[p->num];
                }
                if (--v[p->num].indegree==0)  //如果入度变为0则入栈
                {
                    s.push(p->num);
                }
            }
        }
    }
    return max;
}
int main() {
    int n, m;
    cin >> n >> m;
    createGraph(n, m);
    Stack s(n);
    int max = topoSort(s, n);
    cout << max << endl;
    return  0;
}