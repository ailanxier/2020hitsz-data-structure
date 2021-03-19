#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MININTEGER 0

#define MAX(a,b) ((a>b) ? a : b)
int bucket[100];//18到65的桶
//函数功能：返回快递员相邻年龄间隔的最大值
int maximumGap(){
    int maxGap = -1;//最大间隔
    int last = 0;//相邻的上一个年龄
    for(int i = 18;i <= 65;i++){
        if(bucket[i]&&last != 0) maxGap = MAX(maxGap,i-last),last = i;
        else if(bucket[i]&&last == 0 ) last = i;//第一个年龄
    }
    return maxGap;
}
int main()
{
    int numsSize;  //快递员数量
    int count = 0; //测试用例编号
    int maxdiff;   //相邻年龄间隔的最大值
    freopen("5_2_input.in", "r", stdin);

    while(scanf("%d",&numsSize)!=EOF){
        memset(bucket,0,sizeof(bucket));
        count++;
        int nums[numsSize];  //快递员年龄数组
        for(int i = 0;i < numsSize;i++){
            scanf("%d",&nums[i]);
            //年龄规定在18-65之间
            if(nums[i]>65||nums[i]<18){
                printf("年龄不在18岁到65岁之间");
                exit(0);
            }
            bucket[nums[i]] = 1;//将该年龄记录在桶中
        }
        printf("======Case %d======\n",count);
        maxdiff = maximumGap();
        printf("%d\n", maxdiff);

    }
    fclose(stdin);

    return 0;
}
