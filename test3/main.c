
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
//定义树节点的结构体
typedef struct Node
{
    char data;
    struct Node *lchild, *rchild;
} TreeNode, *BiTree;

int leafSum = 0;//在任务3中记录叶子总数
int floorSum[100];//在任务3中记录每一层的结点数，取最大值得到宽度
int Depth = 0;//在任务3中记录二叉树的深度

//递归建立二叉树
BiTree createBiTree()
{
    //建立一棵新二叉树
    BiTree newTree = (BiTree)malloc(sizeof(TreeNode));
    if(newTree == NULL) {
        printf("OVERFLOW");
        exit(0);
    }
    char data;//输入根节点字符
    data = (char)getchar();
    if(data == '#') newTree = NULL;//字符输入#相当于空树
    else{
        newTree->data = data;
        newTree->lchild = createBiTree();//递归建立左子树，同样会返回子树根节点
        newTree->rchild = createBiTree();//同
    }
    return newTree;
}

//访问某一节点
void visit(BiTree p){
    printf("%c",p->data);
}

//函数功能：前序遍历
void preOrderTraverse(BiTree p)
{
    if(p == NULL) return;
    visit(p);
    preOrderTraverse(p->lchild);
    preOrderTraverse(p->rchild);
}

//函数功能：中序遍历
void inOrderTraverse(BiTree p)
{
    if(p == NULL) return;
    inOrderTraverse(p->lchild);
    visit(p);
    inOrderTraverse(p->rchild);
}

//函数功能：后序遍历
void postOrderTraverse(BiTree p)
{
    if(p == NULL) return;
    postOrderTraverse(p->lchild);
    postOrderTraverse(p->rchild);
    visit(p);
}

//函数功能：根据后序与中序序列构造二叉树，并返回根节点
//参数说明：post[]为后序序列，postStart,postEnd为后序的第一和最后一个节点下标，in[]为中序序列，inStart,inEnd为中序的第一和最后一个节点下标。
BiTree PostInCreate(char post[],int postStart,int postEnd,char in[],int inStart,int inEnd)
{
    BiTree newTree = (BiTree)malloc(sizeof(TreeNode));
    if(newTree == NULL) {
        printf("OVERFLOW");
        exit(0);
    }
    char rootData = post[postEnd];//后序序列的最后一个结点是根
    newTree->data = rootData;
    newTree->lchild = NULL;
    newTree->rchild = NULL;
    //后序序列长度和中序序列不一致，返回错误
    if(postEnd-postStart != inEnd-inStart){
        printf("Unable to build a binary tree.\n");
        exit(0);
    }
    //如果序列中只剩下一个元素，肯定是叶子结点
    if(postEnd == postStart) {
        //判断最后两个元素是否相等，不等还是不能构成二叉树
        if(rootData != in[inStart]){
            printf("Unable to build a binary tree.\n");
            exit(0);
        }
        return newTree;//直接返回，不再构造其子树
    }
    int mid = inStart;//mid在中序序列中找到根节点
    for(;mid<=inEnd;mid++){
        if(in[mid] == rootData) break;
        //如果最后一个但是还是没找到，说明不能构成一棵二叉树
        else if(mid==inEnd){
            printf("Unable to build a binary tree.\n");
            exit(0);
        }
    }
    int leftLen = mid - inStart;//左子树的序列长度（即包含结点数）
    int rightLen = inEnd - mid;//右子树的序列长度
    //通过左右子树序列长度将原序列继续划分为左子树和右子树的后序和中序序列
    if(leftLen)newTree->lchild = PostInCreate(post,postStart,postStart+leftLen-1,in,inStart,inStart+leftLen-1);
    if(rightLen)newTree->rchild = PostInCreate(post,postEnd-rightLen,postEnd-1,in,inEnd-rightLen+1,inEnd);
    return newTree;
}

//函数功能：递归计算叶子节点和二叉树宽度数
//参数：该depth深度的子树根节点root
void countLeafSumAndWidth(BiTree root,int depth)
{
    floorSum[depth]++;//该层节点数增一
    //判断是否为叶子结点（左右子树都是空的）
    if(root->lchild == NULL&&root->rchild == NULL) {
            leafSum++;
            Depth = Depth>=depth?Depth:depth;//深度取最大值
            return;
    }
    if(root->lchild != NULL) countLeafSumAndWidth(root->lchild,depth+1);
    if(root->rchild != NULL) countLeafSumAndWidth(root->rchild,depth+1);
}

//函数功能：判断两树是否等价
//参数说明：bt1:第一个二叉树，bt2:第二个二叉树
int isEquivalent(BiTree bt1,BiTree bt2)
{
    //如果两颗树同时为空，说明到这里为止都是等价的
    if(bt1 == NULL && bt2 == NULL) return 1;
    //如果不同时为空，则不等价，直接返回
    else if((bt1 == NULL && bt2 != NULL )||(bt1 != NULL && bt2 == NULL )) return 0;
    //根节点相同才有资格判断孩子是否相同
    if(bt1->data == bt2->data){
        //递归判断左子树和右子树是否相同
        if(isEquivalent(bt1->lchild,bt2->lchild)&&isEquivalent(bt1->rchild,bt2->rchild)) return 1;
        else return 0;
    }
    else return 0;
}

//任务1：实现二叉树先序、中序、后序遍历
void task1(BiTree bt){
    if(bt == NULL) {
        printf("This is an empty tree.\n");
        return;
    }
    printf("start task (1) Create Tree in PreOrder\n");
    printf("preOrderTraverse：\n");
    preOrderTraverse(bt);//先序遍历
    printf("\n");
    printf("inOrderTraverse：\n");
    inOrderTraverse(bt);//中序遍历
    printf("\n");
    printf("postOrderTraverse：\n");
    postOrderTraverse(bt);//后序遍历
    printf("\n");
}

//任务2：请利用PostInCreate函数根据后序与中序序列构造二叉树
//使用函数：PostInCreate
void task2(BiTree *bt){
    printf("------------------------------------------------\n");
    printf("start task (2) Input the postOrder and inOrder Sequence ,Then build the tree\n");
    char post[31];   //后序序列
    char in[31];      //中序序列
    int postLen;     //后序序列长度
    int inLen;        //中序序列长度
    printf("please input the postOrder sequence\n");
    scanf("%s",post+1);
    printf("please input the inOrder sequence\n");
    scanf("%s",in+1);
    postLen = (int)strlen(post + 1);//将第一个字符下标移到1，方便使用
    inLen = (int)strlen(in + 1);
    //数组长度过长，越界两个序列长度不一致
    if(postLen > 30 || inLen > 30 || postLen != inLen){
        printf("Unable to build a binary tree.\n");
        exit(0);
    }
    *bt = PostInCreate(post, 1, postLen, in, 1, inLen);
    printf("preOrderTraverse:\n");
    preOrderTraverse(*bt);
    printf("\n");
}

//任务3：计算二叉树的叶节点个数和宽度
//使用函数：countLeafSum
void task3(BiTree bt){
    countLeafSumAndWidth(bt,1);
    printf("------------------------------------------------\n");
    printf("start task (3)\n");
    printf("The number of leaf nodes of the tree is: %d\n",leafSum);
    int maxSum = 0;//遍历一遍找到宽度
    for(int i = 1;i <= Depth;i++) maxSum = maxSum>=floorSum[i]?maxSum:floorSum[i];
    printf("The width of the tree is:%d\n",maxSum);
}

//任务4：判断两个二叉树是否等价
//使用函数：isEquivalent
void task4(BiTree bt1,BiTree bt2){
    printf("------------------------------------------------\n");
    printf("start task (4) Are two Bitrees equivalent?\n");
    printf("%d\n",isEquivalent(bt1,bt2));
}

int main(){
    system("color f9");//白色背景，湖蓝字体
    memset(floorSum,0,sizeof(floorSum));//统计每层结点数
    BiTree bt1,bt2;//两个任务分别构造的树
    printf("Create Tree1 in PreOrder\n");

    //任务1：按照先序序列构造二叉树
    bt1=createBiTree();
    //如果bt1是颗空树，会在任务1中提示，并不进行遍历
    //按先序、中序、后序遍历二叉树
    task1(bt1);

    //任务2：按中序和后序构造二叉树
    task2(&bt2);

    //任务3：统计任务2中二叉树叶子结点数和宽度
    task3(bt2);

    //任务4：判断任务1和任务2中两颗树是否等价
    task4(bt1,bt2);

    return 0;
}
