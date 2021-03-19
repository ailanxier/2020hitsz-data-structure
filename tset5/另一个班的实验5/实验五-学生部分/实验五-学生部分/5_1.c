#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//请实现排序算法,可自定义参数
void resort(int* arr,int num){

}
//找到两个集合的交集,可自定义参数
void set_join_set(int *set1, int *set2, int num1, int num2){

}
int main()
{
    int set_len_1,set_len_2,caseNum=0;
    freopen("5_1_input.in", "r", stdin);
    while(scanf("%d %d",&set_len_1,&set_len_2)!=EOF){
        caseNum++;
        int set1[set_len_1];
        int set2[set_len_2];
        printf("==== Case %d ====\n",caseNum);
        for(int i=0;i<set_len_1;i++)
            scanf("%d",&set1[i]);
        for(int i=0;i<set_len_2;i++)
            scanf("%d",&set2[i]);
        resort(set1, set_len_1);
        resort(set2, set_len_2);
        set_join_set(set1, set2, set_len_1, set_len_2);
    }
    fclose(stdin);
}
