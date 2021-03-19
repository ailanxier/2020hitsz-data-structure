#include <stdio.h>
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

//在某一坐标轴上建立邮局，返回各点到邮局在这个坐标轴上的最小距离
int getDistance(int *position,int n){
    int dis = 0;
    int post = position[1];//邮局的位置，初始为第一个点的位置
    for(int i = 2;i <= n;i++) dis += position[i] - post;
    int ans = dis;//保留最小的dis
    int last = position[1];
    //遍历每一个房子在坐标轴上划分的区域
    for(int i = 2;i <= n;i++){
        //去重
        if(position[i] == last) continue;
        //遍历区域上的每一个点
        for(int j = position[i-1]+1;j <= position[i];j++){
            dis = dis + i-1-(n-i+1);//转移公式
            ans = min(dis,ans);//取最小值
        }
        last = position[i];
    }
    return ans;
}

/** 返回最短距离之和 */
int minTotalDistance(int *x,int *y,int n){
    int minDisOnX = getDistance(x,n);//在x轴上
    int minDisOnY = getDistance(y,n);//在y轴上
    return minDisOnX+minDisOnY;
}

int main()
{
    int n;
    // 文本输入方式
    freopen("5_1_input.in", "r", stdin);
    int caseNum = 0;
    while (scanf("%d", &n) != EOF){
        printf("======Case %d======\n",++caseNum);
        int x[n+1], y[n+1]; // 坐标数组,用于保存X坐标和Y坐标
        for (int i = 1; i <= n; i++)  scanf("%d%d", &x[i], &y[i]);
        //x与y坐标相互独立，各自升序排列
        sort(x,1,n);
        sort(y,1,n);
        printf("Min total distance: %d\n", minTotalDistance(x,y,n));
    }
    fclose(stdin);
    return 0;
}
