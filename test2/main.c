#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StackNode{
    /** 栈中存储的节点 */
  int id;
  struct StackNode *next;
}sNode;

typedef struct LinkStack{
    /** 链栈 */
  sNode* top;
  int size;
}Stack;

Stack* InitStack(){
    /** 初始化栈 */
  Stack* stack = (Stack *)malloc(sizeof(Stack));
  stack->top = NULL;
  stack->size = 0;
  return stack;
}

int StackEmpty(Stack *stack){
    /** 判断栈是否为空 */
  return (stack->size == 0);
}

void Push(Stack *stack,int element){
    /** 将一个节点压入栈 */
    sNode * newNode = (sNode *)malloc(sizeof(sNode));
    if(newNode == NULL){
        printf("OVERFLOW");
        exit(0);
    }
    newNode->id = element;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

void Pop(Stack* stack){
    /** 将一个节点弹出栈 */
    if(StackEmpty(stack)) return;//空栈直接返回
    sNode *temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
}

int Top(Stack* stack){
    /** 若栈不空，返回栈的栈顶元素 */
    if(StackEmpty(stack)) return 0;//空栈返回0
    return stack->top->id;
}

/** 实验内容1:判断输入的出站序列in是否可由输入的进站序列out通过进出栈得到
     可行返回1，不可行返回0
     num 是 进站火车数 */
int SeqLegal(int in[],int out[],int num){
    Stack * stack = InitStack();
    int inNum = 1,outNum = 1;
    for(; inNum <= num ; inNum++){
        //如果要进站的这个不会马上出去，就先进栈
        if(in[inNum] != out[outNum])  Push(stack,in[inNum]);
        else   outNum++;
        // 如果栈不为空并且栈顶火车就等于出站的火车，退栈
        while(! StackEmpty(stack) && Top(stack) == out[outNum]){
            Pop(stack);
            outNum++;
        }
        //如果火车已经全部进站，但是却没有在while循环中全部按所给顺序出站，说明不可能按此序列出站
        if(inNum == num && ! StackEmpty(stack)) return 0;
    }
    return 1;
}

typedef struct QueueNode{
    /** 队列节点 */
    int id;
    struct QueueNode* next;
}qNode;

typedef struct Queue{
    /** 队列 */
    qNode *front;
    qNode *rear;
    int size;
}Queue;

Queue* InitQueue(){
    /** 初始化队列 */
    Queue* linkQueue = (Queue*) malloc(sizeof(Queue));
    linkQueue->front = linkQueue->rear = (qNode *)malloc(sizeof(qNode));
    linkQueue->front->next = NULL;
    linkQueue -> size = 0;
    return linkQueue;
}

int QueueEmpty(Queue* linkQueue){
    /** 判断队列是否为空 */
    return (linkQueue->front == linkQueue->rear);
}

void EnQueue(Queue *linkQueue,int element){
    /** 入队 */
    qNode * newNode = (qNode *)malloc(sizeof(qNode));
    if(newNode == NULL){
        printf("OVERFLOW");
        exit(0);
    }
    newNode->id = element;
    newNode->next = NULL;
    linkQueue->rear->next = newNode;
    linkQueue->rear = newNode;
    linkQueue->size++;
}

void DeQueue(Queue *linkQueue){
    /** 出队 */
    if(QueueEmpty(linkQueue)) return;//空队列直接返回
    qNode * temp = linkQueue->front;
    linkQueue->front = linkQueue->front->next;
    free(temp);
    linkQueue->size--;
}

int QueueLength(Queue *linkQueue){
    /** 队列长度 */
    return linkQueue->size;
}

int GetHead(Queue *linkQueue){
    /** 返回队头 */
    if(QueueEmpty(linkQueue)) return 0;//空队列返回0
    return linkQueue->front->id;
}

int GetRear(Queue *linkQueue){
    /** 返回队尾 */
    if(QueueEmpty(linkQueue)) return 0;//空队列返回0
    return linkQueue->rear->id;
}

/**  找到最合适的火车轨道 */
int findClosestQueue(Queue *railQueue[],int usedQueue,int curTrain){

    int closestIdx = 1;
    /**
    *   用二分法找到第一个队列中队尾元素值比curTrain小的轨道序号
    *   使各轨道最后一辆火车的序号递减排列
    */
    int left = 1;
    int right = usedQueue;
    //如果还没有任何火车进站 或者 最后一条轨道的最后一辆火车都比现在这辆火车的序号大，这说明要再开一条轨道
    if(usedQueue == 0 || GetRear(railQueue[right]) > curTrain) return usedQueue + 1;
    while(left <= right){
        closestIdx = (left+right)/2;
        if(GetRear(railQueue[closestIdx]) > curTrain) left = closestIdx + 1;
        else right = closestIdx - 1;
    }
    return closestIdx;
}

/** 实验内容2:求解所需缓冲轨道的最小值,返回这个最小值*/
int minBufferQueue(int in[],int num){

    Queue *railQueue[num+1];
    //指针数组，记录各缓存轨道的火车，有与火车数相等的轨道数时一定可行
    for(int i = 1;i <= num;i++){
        railQueue[i] = InitQueue();
    }
    int usedQueue = 0;      //已使用的轨道数

    for(int i = 1;i <= num;i++){
        //调用函数获取最合适放置的轨道
        int closetNum = findClosestQueue(railQueue,usedQueue,in[i]);
        //如果这个最适规道数比已使用的轨道数大，就将已使用的轨道数加1（最适轨道数只可能是已用轨道数+1）
        if(closetNum>usedQueue) usedQueue++;
        //入队
        EnQueue(railQueue[closetNum],in[i]);
    }

    return usedQueue;
}

int main()
{
    int trainNum;
    int count = 0;
    freopen("Train.in", "r", stdin);
    //trainNum是本次火车总共要进站的数量
    while(scanf("%d",&trainNum)!=EOF){
        count++;//情况计数器
        int trainIn[trainNum+1];// 存储进来的火车编号序列
        int trainOut[trainNum+1];// 存储出去的火车编号序列
        //从下标1开始接收
        for(int i = 1;i <= trainNum;i++){
            //非法输入控制
            while(!scanf("%d",&trainIn[i])){
                printf("The input data is illegal,please input again:\n");
                fflush(stdin);
            }
        }
        for(int i = 1;i <= trainNum;i++){
            //非法输入控制
            while(!scanf("%d",&trainOut[i])){
                printf("The input data is illegal,please input again:\n");
                fflush(stdin);
            }
        }
        printf("\n============Case %d============\n\n",count);
        printf("Experiment 1 :Judge Possibility:\n");
        // 实验内容1  火车按照给定顺序进站，判断是否可以按给定顺序出站
        if(SeqLegal(trainIn,trainOut,trainNum)){
            printf("The output train sequence is Possible\n");
        }else{
            printf("The output train sequence is impossible\n");
        }
        // 实验内容2
        printf("-----------------------------------\nExperiment 2:Get MinBuffer:\n");
        printf("The recover the order, %d buffer queue is needed\n",minBufferQueue(trainOut, trainNum));
    }
    fclose(stdin);
    return 0;
}



