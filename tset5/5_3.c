#include<stdio.h>
#include <stdlib.h>
//返回最大值
int max(int n1,int n2){
    return n1>n2?n1:n2;
}
//返回最小值
int min(int n1,int n2){
    return n1>n2?n2:n1;
}
//交换
void swap(int *n1,int *n2){
    int tem = *n1;
    *n1 = *n2;
    *n2 = tem;
}
/** 快速排序 */
void sort(int * arr, int l,int r){
    int mid = arr[(l+r)/2];//主元
    int i = l,j = r;//保留原来的左端点和右端点
    while(i <= j){
        while(arr[i]<mid) i++;
        while(mid<arr[j]) j--;
        if(i <= j){
            swap(arr+i,arr+j);
            i++,j--;
        }
    }
    if(j>l)  sort(arr,l,j);//递归排序
    if(i<r) sort(arr,i,r);
}

//实现函数功能，返回至少的邮递员人数。
int getMinNum(const int *array, int n){
    int peopleNum=n;//邮递员数量,初始化为回答的人的数量
    int sameAns = array[1];//相同回答的值
    int sameCount = 0;//相同回答的计数
    for(int i  =2;i <= n;i++){
        //回答与前一位相同
        if(array[i] == sameAns){
            sameCount++;//相同回答数增一
            if(sameCount == sameAns) sameCount = -1;//如果凑成一组，就将计数置为-1
        }
        else {
            //如果回答不相同，且上一位回答没有凑成一组
            if(sameCount != -1) peopleNum+=sameAns-sameCount;
            sameAns = array[i];
            sameCount = 0;
        }
    }
    //处理末尾情况，如果最后一个数没有凑成一组，就加上
    if(sameCount != -1) peopleNum+=sameAns-sameCount;
    return peopleNum;
}

int main(){

    int n,caseNum = 0;//参与回答的邮递员数目
    //文件输入输出
    freopen("5_3_input.in", "r", stdin);
    while(scanf("%d",&n)!=EOF){
        printf("======Case %d======\n",++caseNum);
        int array[n+1];
        for(int i=1;i<=n;i++)  scanf("%d",&array[i]);
        sort(array,1,n);
        printf("There are at least %d postmen.\n", getMinNum(array, n));
    }
    fclose(stdin);
    return 0;
}
