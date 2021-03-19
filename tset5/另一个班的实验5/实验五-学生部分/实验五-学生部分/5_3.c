#include <stdio.h>
#include <stdlib.h>

//对起始时间与终止时间进行排序，参数可自行填写
void sort(int *start,int *end,int M){
}

//计算空闲人数最多的起始时间和终止时间，参数可自行填写
void findPeriod(int *start,int *end,int M,int N){
   
}

int main()
{
   int N, M; //分别存储时间的段数和学生的个数
   int caseNum = 0;
   
   freopen("5_3_input.in", "r", stdin);
   while(scanf("%d %d",&N,&M)!=EOF){
       int start[M];
       int end[M];
       caseNum++;
       printf("==== Case %d ====\n",caseNum);
       for(int i = 0; i < M;i++){
           scanf("%d %d",&start[i],&end[i]);
       }
       sort(start, end, M);
       findPeriod(start, end, M, N);
   }
   fclose(stdin);

   /* 终端输入
   while(scanf("%d %d",&N,&M)!=EOF){
       int start[M];
       int end[M];
       caseNum++;
       printf("==== Case %d ====\n",caseNum);
       for(int i = 0; i < M;i++){
           scanf("%d %d",&start[i],&end[i]);
       }
       sort(start, end, M);
       findPeriod(start, end, M, N);
   }
   */
}

