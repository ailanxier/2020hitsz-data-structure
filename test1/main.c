
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int ClassID;
    int StuID;
    int Grade;
    struct node *next;
}StudentLinkedListNode;

/** 打印单个节点 */
void printLinkedListNode(StudentLinkedListNode * node){
    printf("{name:%d, ID:%d, Grade:%d}",node->ClassID, node->StuID, node->Grade);
    if(node->next!=NULL){
        printf("->");
    }else{
        printf("\n");
    }
}

/** 输出该表的成绩情况 */
void outputStudentLinkedList(StudentLinkedListNode* head){
    //用于单个节点输出的函数printLinkedListNode已提供
    //检查是否为空表
    if(head == NULL||head->next == NULL){
        printf("当前为空表，请先输入数据");
        return;
	}
	StudentLinkedListNode * nowNode = head->next;
	//当nowNode不为空时，输出他的元素值并下移,直到链表末尾
	while(nowNode != NULL){
        printLinkedListNode(nowNode);
        nowNode = nowNode->next;
	}
}

/** 新建一个链表node并返回地址 */
StudentLinkedListNode* studentLinkedListCreate( int class_id,int student_id,int grade) {
    //tips:malloc的时候记得为转化为结构体指针
	//TODO
	StudentLinkedListNode * newStudentNode = (StudentLinkedListNode *)malloc(sizeof(StudentLinkedListNode));
	//检查是否申请成功
	if(newStudentNode == NULL){
        printf("内存不足");
        exit(0);
	}
	newStudentNode->ClassID = class_id;
	newStudentNode->Grade = grade;
	newStudentNode->StuID = student_id;
	newStudentNode->next = NULL;
	return newStudentNode;//返回新节点地址
}

/** copy一个已有的node */
StudentLinkedListNode* studentLinkedListCopy(StudentLinkedListNode* src){
    StudentLinkedListNode* tempNode = studentLinkedListCreate(src->ClassID,src->StuID,src->Grade);
    return tempNode;
}

/** 按照降序插入学生的成绩情况,并返回链表头指针 */
StudentLinkedListNode* studentLinkedListAdd(StudentLinkedListNode* head, StudentLinkedListNode* node) {
    //先检查表头节点是否为空
    if(head == NULL){
        head = (StudentLinkedListNode *)malloc(sizeof(StudentLinkedListNode));
        if(head == NULL){
            printf("内存不足");
            exit(0);
        }
    }
    //再检查是否是空表
    if(head->next == NULL){
        head->next = node;
        node->next = NULL;
    }
    else{
        StudentLinkedListNode * nowNode = head->next;//指向当前节点
        StudentLinkedListNode * priorNode = head;//保留当前节点上一个节点
        if(node->Grade > nowNode->Grade){//如果输入的新节点成绩已经大于当前最靠前的成绩，就要修改head->next的指向
            head->next = node;
            node->next = nowNode;
        }
        else{
            //nowNode下移找到第一个不小于node成绩值的节点
            while(node->Grade < nowNode->Grade){
                priorNode = nowNode;
                nowNode = nowNode->next;
                 //如果当前链表所有节点成绩都比node小，退出
                if(nowNode == NULL)
                   break;
            }
            //此时node不比nowNode成绩值小，比priorNode小，插入中间
            priorNode->next = node;
            node->next = nowNode;
        }
    }
    return head;
}

/** 根据学号搜索某个学生的成绩情况 如果没有,请printf("this class  has no such student as id=%d",id)； */
void searchByID(StudentLinkedListNode * head ,int id){
    //该班级成绩表为空表,直接输出
    if(head == NULL||head->next == NULL){
        printf("this class has no such student as id=%d",id);
        return;
    }
    StudentLinkedListNode * nowNode = head->next;
    //当nowNode不为空时，比较他的学号
    while(nowNode != NULL){
        if(nowNode->StuID == id){
            printf("班级：%d  学号：%d  成绩：%d\n",nowNode->ClassID,id,nowNode->Grade);
            return;
        }
        nowNode = nowNode->next;
    }
    //没有在while中return,没有找到该学生的信息
    printf("this class  has no such student as id=%d",id);
}

/** 根据学号删除某个学生的成绩情况 如果没有,请printf("this class has no such student as id=%d",id);*/
StudentLinkedListNode* deleteByID(StudentLinkedListNode* head,int id){
    //该班级成绩表为空表,直接输出
    if(head == NULL||head->next == NULL){
        printf("this class has no such student as id=%d",id);
        return head;
    }
    StudentLinkedListNode * nowNode = head->next;
    StudentLinkedListNode * priorNode = head;
    //当nowNode不为空时，比较他的学号
    while(nowNode != NULL){
        if(nowNode->StuID == id){
            //让nowNode上一个节点指向nowNode下个节点，然后再释放nowNode
            priorNode->next = nowNode->next;
            free(nowNode);
            printf("the student id=%d is deleted",id);
            return head;
        }
        //priorNode保存当前节点，nowNode下移
        priorNode = nowNode;
        nowNode = nowNode->next;
    }
    //没有在while中return,没有找到该学生的信息
    printf("this class  has no such student as id=%d",id);
    return head;
}

/** 合并两个班级的成绩情况，返回新表头指针*/
StudentLinkedListNode* mergeLinkedList(StudentLinkedListNode * heads[]){
    //tips:因为传入的都是指针,为了防止拆分过程中影响了原来总链表的存储,
    //在链表node赋值的时候可以用上面提供的studentLinkedListCopy函数
    //如 node->next = temp_node 改为 node->next = studentLinkedListCopy(temp_node)

    StudentLinkedListNode * nowNode_0 ;//指向0班节点的指针
	StudentLinkedListNode * nowNode_1 ;//指向1班节点的指针
	//检查是否为空表
	if(heads[0] == NULL) nowNode_0 = NULL;//空表置指针为空，在while中会自动跳过
	else nowNode_0 = heads[0]->next;//否则指向第一个节点
	if(heads[1] == NULL) nowNode_1 = NULL;
	else nowNode_1 = heads[1]->next;
	//新链表表头指针
	StudentLinkedListNode * newHead = (StudentLinkedListNode *)malloc(sizeof(StudentLinkedListNode));
	//这里要检查新申请的节点是否申请成功
	if(newHead == NULL){
        printf("内存不足");
        exit(0);
	}
	//建立新链表的节点
	StudentLinkedListNode * newNode = newHead;
	while(nowNode_0 != NULL && nowNode_1 != NULL){
        //newNode指向成绩较大节点的复制节点
        if(nowNode_0->Grade >= nowNode_1->Grade) {
             newNode->next = studentLinkedListCopy(nowNode_0);
             nowNode_0 = nowNode_0->next;
        }else{
            newNode->next = studentLinkedListCopy(nowNode_1);
            nowNode_1 = nowNode_1->next;
        }
        newNode = newNode->next;
	}
	//对于还有的部分直接添加进新链表中，由于原表的降序性，新表一定是降序的
	while(nowNode_0 != NULL){
        newNode->next = studentLinkedListCopy(nowNode_0);
        nowNode_0 = nowNode_0->next;
        newNode = newNode->next;
	}
	while(nowNode_1 != NULL){
        newNode->next = studentLinkedListCopy(nowNode_1);
        nowNode_1 = nowNode_1->next;
        newNode = newNode->next;
	}
	newNode->next = NULL;
	//返回新链表的头指针
    return newHead;
}

/**链表反转，返回新表头指针*/
StudentLinkedListNode* reverseLinkedList(StudentLinkedListNode * head){
    //检查是否为空表,或者只有一个元素，直接返回原头结点，不用反转
    if(head == NULL || head->next == NULL || head->next->next == NULL)
        return head;
    StudentLinkedListNode * nowNode = head->next;
    StudentLinkedListNode * newHead = (StudentLinkedListNode * )malloc(sizeof(StudentLinkedListNode));
    //检查是否申请成功
    if(newHead == NULL){
        printf("内存不足");
        exit(0);
    }
    //newNode为新链表中的新节点，用来反向建立链表
    StudentLinkedListNode * newNode = NULL;
    while(nowNode != NULL){
        //temp保留nowNode的备份，让他指向newNode指向的地址，newNode再指向他
        StudentLinkedListNode * temp = studentLinkedListCopy(nowNode);
        temp->next = newNode;
        newNode = temp;
        nowNode = nowNode->next;
    }
    //将新链表头指针next指向newNode
    newHead->next = newNode;
    return newHead;
}

/**遍历链表确认是否有重复的学号*/
_Bool isExistStudentId(StudentLinkedListNode * head, int id){
    //空表直接返回没有重复学号
    if(head == NULL|| head->next == NULL) return 0;
    StudentLinkedListNode * nowNode = head->next;
    while(nowNode != NULL){
        if(nowNode->StuID == id) return 1;
        nowNode = nowNode->next;
    }
    return 0;
}

int main(){
        system("color 7d");//输出窗口变色
        StudentLinkedListNode* Class[2]={NULL};
        StudentLinkedListNode* All=NULL;
		StudentLinkedListNode* reAll=NULL;
        printf("1.insert 2.search by StuID 3.delete by StuID  4.merge 5.reverse 6.output 7.exit  \n");

        int option;
        int dataRow;
        int tempClass;
        int tempStuId;
        int tempGrade;
        StudentLinkedListNode *tempNode;//保存输入学生信息的节点
        while (scanf("%d", &option) != EOF) {
            fflush(stdin);//防止程序崩溃
            switch (option) {
                case 1:
                    //输入信息
                    printf("How many rows of data do you need to input?\n");
                    //一行是一个学生的信息
                    while(scanf("%d",&dataRow)!=1){
                        printf("输入的信息中含非法字符，请检查输入格式再请重新输入：\n");
                        fflush(stdin);
                    }
                    //提示输入的dataRow少于1行，不合法
                    if(dataRow <= 0){
                        printf("输入的数据行数不能少于1");
                        break;
                    }
                    fflush(stdin);//清除输入行数缓存
                    printf("input the %d row data format as:class_id,student_id,grade\n",dataRow);
                    while (dataRow!=0){
                        //输入的数据异常，含非法字符
                        while(scanf("%d,%d,%d", &tempClass,&tempStuId, &tempGrade)!=3){
                            printf("输入的信息中含非法字符，请检查输入格式再请重新输入：\n");
                            fflush(stdin);
                        }
                        //限制输入班级数为1或2，限制成绩不能低于0分，限制学号不能为负数
                        if(tempClass != 0 && tempClass != 1){
                            printf("输入班级数仅为0或1,请重新输入：\n");
                            continue;
                        }
                        if(tempGrade < 0){
                            printf("输入的成绩低于0分，不合法,请重新输入：\n");
                            continue;
                        }
                        if(tempStuId < 0){
                            printf("输入的学号不能小于0，请重新输入：\n");
                            continue;
                        }
                        if(isExistStudentId(Class[tempClass],tempStuId)){
                            printf("学号为%d的学生信息已存在，请重新输入：\n",tempStuId);
                            continue;
                        }
                        //加个判断学号重复
                        tempNode = studentLinkedListCreate(tempClass, tempStuId, tempGrade);
                        Class[tempClass]=studentLinkedListAdd(Class[tempClass], tempNode);
                        dataRow--;
                    }
                    break;
                case 2:
                    //根据学号搜索某个学生的成绩情况
                    printf("input the data format as: ClassID, StuID\n");
                    //输入的数据异常，含非法字符
                    while(scanf("%d,%d,%d", &tempClass,&tempStuId)!=2){
                        printf("输入的信息中含非法字符，请检查输入格式再请重新输入：\n");
                        fflush(stdin);
                    }
                    //检查输入的班级和学号是否符合要求,如果班级不为1或0，学号小于0，直接输出未找到
                    if((tempClass != 0 && tempClass != 1)||tempStuId < 0 ){
                        printf("this class has no such student as id=%d",tempStuId);
                        break;
                    }
                    searchByID(Class[tempClass],tempStuId);
                    break;
                case 3:
                    //根据学号删除某个学生的信息
                    printf("input the data format as: ClassID, StuID\n");
                    //输入的数据异常，含非法字符
                    while(scanf("%d,%d,%d", &tempClass,&tempStuId)!=2){
                        printf("输入的信息中含非法字符，请检查输入格式再重新输入：\n");
                        fflush(stdin);
                    }
                    //检查输入的班级和学号是否符合要求,如果班级不为1或0，学号小于0，直接输出未找到
                    if((tempClass != 0 && tempClass != 1)||tempStuId < 0){
                        printf("this class has no such student as id=%d",tempStuId);
                        break;
                    }
                    Class[tempClass]=deleteByID(Class[tempClass], tempStuId);
                    break;
                case 4:
                    //合并链表
                    All=mergeLinkedList(Class);
                    outputStudentLinkedList(All);
                    break;
                case 5:
                    //翻转链表
                    reAll=reverseLinkedList(All);
                    outputStudentLinkedList(reAll);
                    break;
                case 6:
                    //输出链表
                    printf("Class 0:\n");
                    outputStudentLinkedList(Class[0]);
                    printf("\nClass 1:\n");
                    outputStudentLinkedList(Class[1]);
                    break;
                case 7:
                    //结束循环，退出程序
                    exit(0);
                default:
                    //错误指令的提示
                    printf("指令只能为1-6之间的某个整数值.\n");
                    break;
            }
            fflush(stdin);//清除缓存
            printf("\n###################################\n");
            printf("1.insert 2.search by studentID 3.delete by studentID 4.merge 5. reverse 6.output 7.exit \n");
    }
    return 0;
}
