#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxn 10020
#define maxm 200020
#define INF 2147483647
/**
    实验内容二
*/
int ans[maxn];
typedef struct Edge{
    int to,weight,next;
}Edge;

struct Graph{
    Edge edges[maxm];
    //head[i] 记录的是以i为起点的边集中第一条边在edges中的index
    int head[maxn];
    //当前第几条边
    int tot;
};

struct Graph *init_graph(){
    struct Graph *new_grapth = (struct Graph *)malloc(sizeof(struct Graph));
    new_grapth->tot = 0;
    memset(new_grapth->head, -1, sizeof(new_grapth->head));
    return new_grapth;
}

//加边函数:链式前向星存储，每加一条边的时候，同一起点的边用next来做链式存储
void add_edge(int start, int end, int weight, struct Graph *graph){
    graph->edges[++graph->tot].to = end;
    graph->edges[graph->tot].weight = weight;
    graph->edges[graph->tot].next = graph->head[start];
    graph->head[start] = graph->tot;
}

//遍历有向无环图，input_array是输入层结点的初始权值
void forward_propagation(int n_total, int n_input, int n_output, int *input_array, struct Graph *graph){
    memset(ans,0,sizeof(ans));
    int vis[maxn] = {0};//是否被访问过
    int q[maxn] = {0};//存放隐藏层神经元的队列
    int left = 0;//队列左端
    int right = 0;//队列右端
    int nowD;
    //遍历输入层每一个结点,得到第一层的隐藏层结点
    for(int i = 1;i <= n_input;i++) {
        ans[i] = input_array[i];
        for(int j = graph->head[i];j != -1;j = graph->edges[j].next){
            int to = graph->edges[j].to;
            int weight = graph->edges[j].weight;
            ans[to]+=weight*input_array[i];
            //如果该结点没有被加入隐藏层集合中，同时也不是输出层结点，就加入集合
            if(!vis[to]&&graph->head[to]!=-1) q[++right] = to,vis[to] = 1;
        }
    }
    //对每一个隐藏层结点进行遍历
    while(1){
        nowD = q[++left];
        if(nowD ==0) break;//当取出来的结点为0时，代表队列为空
        for(int i = graph->head[nowD];i != -1;i = graph->edges[i].next){
            int to = graph->edges[i].to;
            int weight = graph->edges[i].weight;
            ans[to]+=weight*ans[nowD];
            //如果该结点没有被加入隐藏层集合中，同时也不是输出层结点，就加入集合
            if(!vis[to]&&graph->head[to]!=-1) q[++right] = to,vis[to] = 1;
        }
    }
}

int main(){
    //system("color f9");//白色背景，湖蓝字体
    int input[maxn];
    int n_total, m_total, n_input, n_output;
    //文件输入的方式
    freopen("4_2_input.in", "r", stdin);
    //点数，边数，输入层结点数，输出层节点数
    while (scanf("%d%d%d%d", &n_total, &m_total, &n_input, &n_output) != EOF){
        struct Graph *g = init_graph();
        int start, end, weight;
        //输入边和权值
        for (int i = 1; i <= m_total; i++){
            scanf("%d%d%d", &start, &end, &weight);
            add_edge(start, end, weight, g);
        }
        //输入给输入层的初始权值
        for (int i = 1; i <= n_input; i++)
            scanf("%d", &input[i]);

        //结果保存在全局变量ans数组中
        forward_propagation(n_total, n_input, n_output, input, g);

        //输出输出层所有结点的末权值
        for (int i = n_total - n_output + 1; i <= n_total; i++)
            printf(i < n_total ? "%d " : "%d\n", ans[i]);
    }
    fclose(stdin);
    return 0;
}
