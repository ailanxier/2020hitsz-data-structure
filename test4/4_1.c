#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxn 10020
#define maxm 200020
#define INF 2147483630
/*
    实验内容1
*/
int ans[maxn];
typedef struct Edge
{
    int to,weight,next;
    //该边，同一起点的上一边在edgs中存储的下标。以next作为链式寻找同一起点的所有边
}Edge;

struct Graph
{
    Edge edges[maxm];
    //head[i] 记录的是以i为起点的边集中第一条边在edges中的index,
    int head[maxn];
    //当前第几条边
    int tot;
};

struct Graph *init_graph()
{
    struct Graph *new_grapth = (struct Graph *)malloc(sizeof(struct Graph));
    new_grapth->tot = 0;
    memset(new_grapth->head, -1, sizeof(new_grapth->head));
    return new_grapth;
}

//加边函数:链式前向星存储，每加一条边的时候，同一起点的边用next来做链式存储
void add_edge(int start, int end, int weight, struct Graph *graph)
{
    graph->edges[++graph->tot].to = end;
    graph->edges[graph->tot].weight = weight;
    graph->edges[graph->tot].next = graph->head[start];
    graph->head[start] = graph->tot;
}

//获得最短传播时间的函数，n为顶点数
int get_min_time(int n, int startpoint, struct Graph *graph)
{
    memset(ans,0x3f,sizeof(ans));//将ans置为最大值
    int q[maxn] = {0};//存有被更新最短路的节点的集合
    int vis[maxn] = {0};//节点是否被遍历过
    q[0] = 0;
    q[1] = startpoint; //集合存入起始点
    ans[startpoint] = 0;//起始点到自己距离为1
    int tot = 1;//集合的点数
    int cnt = 0;//用于判断是否已经遍历完所有节点
    int nowD;  //每次遍历的出发点
    while(1){
        nowD = 0;
        //找到当前未遍历且在被更新的节点最短路径者
        for(int i = 1;i <= tot;i++){
            if(!vis[q[i]]) nowD = ans[nowD]>ans[q[i]]?q[i]:nowD;
        }
        if(nowD == 0) break;
        vis[nowD] = 1;
        cnt++;
        //遍历从nowD出发的每一个邻接点
        for(int i = graph->head[nowD];i != -1;i = graph->edges[i].next){
            int to = graph->edges[i].to;
            int weight = graph->edges[i].weight;
            //如果从nowD与to连一条权值为weight的边后，比之前从起始点到to的最短路径还要短，则将to压入集合中
            if(ans[to] > ans[nowD] + weight){
                ans[to] = ans[nowD] + weight;
                q[++tot] = to;//进入集合
            }
        }
    }
    if(cnt < n) return -1;//遍历的点数少于总点数，说明存在孤立点
    int maxTime = 0;//取从起始点出发的最短路径的最大值
    for(int i = 1;i <= n;i++) maxTime = maxTime>ans[i]?maxTime:ans[i];
    return maxTime;
}

int main()
{
    //system("color f9");//白色背景，湖蓝字体
    int n, m, startpoint, min_time;
    //文件读入的方式
    freopen("4_1_input.in", "r", stdin);
    //n为点数，m为边数，startpoint为起点
    while (scanf("%d%d%d", &n, &m, &startpoint) != EOF)
    {
        struct Graph *g = init_graph();//返回空图
        int start, end, weight;
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &start, &end, &weight);
            add_edge(start, end, weight, g);
        }
        //遍历找最短扩散时间
        min_time = get_min_time(n, startpoint, g);
        printf("%d\n", min_time);
    }
    fclose(stdin);
    return 0;
}
