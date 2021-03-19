#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 比较两个字符串，可自定义参数或自定义函数
int str_cmp(char fir[],char sec[]){
   return 0;
}

// 请实现排序算法,可自定义参数
void resort(char arr[][100],int num){
}
int main()
{
    int inputs_size=0,caseNum=0;
    freopen("5_2_input.in", "r", stdin);
    while(scanf("%d",&inputs_size)!=EOF){
        caseNum++;
        char inputs[inputs_size][100];     
        printf("==== Case %d ====\n",caseNum);
        for(int i=0;i<inputs_size;i++)
            scanf("%s",inputs[i]);
        resort(inputs, inputs_size);
    }
    fclose(stdin);
}