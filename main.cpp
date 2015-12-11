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
        if (!v[start].num) {   //��V�еĽڵ㸳ֵ����ÿ�߶˵�����ָ�ֵ��start��end��ͬ
            v[start].num = start;
        }
        if (!v[end].num) {
            v[end].num = end;
        }
        v[start].outdegree++; //start���ȼ�1
        v[end].indegree++; //end��ȼ�1
    }
    for (int i = 1; i <=n; i++)
    {
        int neiboNum = v[i].outdegree;//Ϊÿһ���ڵ㿪neibo����
        if (neiboNum) {
            v[i].neibo = pNode(malloc(neiboNum * sizeof(VertexNode)));
        }
    }
    for (int i = 0; i < m; i++)
    {
        int start = eBegin[i];//����ÿһ���ߣ��ѱ��ϵ�end�ڵ���ӵ�start��neibo��
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
        villages[i] = 1;   //��¼ÿ�����Ӷ�Ӧ���·�����ȣ�Ĭ�϶�Ϊ1
    }
    for (int i = 1; i <=n; i++)
    {
        if (v[i].indegree == 0) {
            s.push(i);  //����ȵ���0�ĵ���ջ
        }
    }
    while (!s.isEmpty())
    {
        int node = s.pop();   //ȡһ�����Ϊ0��node
        for (int i = 0; i < v[node].outdegree; i++)  //����node���е��ھ�
        {
            pNode p = &(v[node].neibo[i]);
            if (p)
            {
                if (villages[node]+1>villages[p->num])//ģ��������һ���Ĺ���
                {
                    villages[p->num] = villages[node] + 1;
                }
                if (max<villages[p->num])  //�����������max
                {
                    max = villages[p->num];
                }
                if (--v[p->num].indegree==0)  //�����ȱ�Ϊ0����ջ
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