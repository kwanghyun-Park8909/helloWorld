#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
printf("�ȳ�");
 typedef struct Student {    //���߿��Ḯ��Ʈ
    struct Student* llink;  //���ʳ�忡 ���� ��ũ
    double height;          //Ű
    char name[50];          //�̸�
    struct Student* rlink;  //������ ��忡 ���� ��ũ
}student;

typedef struct {
    student* start; //����Ʈ����
    student* last;  //����Ʈ��
}line_up;

line_up* createLine_up(void) {  //���� ���߿��Ḯ��Ʈ ����
    line_up* DL;
    DL = (line_up*)malloc(sizeof(line_up));
    DL->start = NULL;
    DL->last = NULL;
    return DL;
}

void print(line_up* DL) {   //����Ʈ�� ������� ���(��������)
    student* p;
    p = DL->start;
    if (DL->start == NULL)
        printf("����ִ� ����Դϴ�.\n");
    else {
        while (p != NULL) {
            printf("%s  (%.0f)\n", p->name, p->height);
            p = p->rlink;
        }
    }
}

void reverseprint(line_up* DL) {    //����Ʈ�� �ڿ������� ���(��������)
    student* p;
    p = DL->last;
    if (DL->start == NULL)
        printf("����ִ� ����Դϴ�.\n");
    else {
        while (p != NULL) {
            printf("%s  (%.0f)\n", p->name, p->height);
            p = p->llink;
        }
    }
}
void insertStudent(line_up* DL, student* pre, student* next, char* x, double h) {   //��� ����
    student* newStudent;
    newStudent = (student*)malloc(sizeof(student));
    newStudent->llink = NULL;
    newStudent->rlink = NULL;
    strcpy(newStudent->name, x);
    newStudent->height = h;
    if (DL->start == NULL) {
        newStudent->rlink = NULL;
        newStudent->llink = NULL;
        DL->start = newStudent;
        DL->last = newStudent;
    }
    else {
        if (next != NULL && pre != NULL) {
            newStudent->rlink = next;
            newStudent->llink = pre;
            next->llink = newStudent;
            pre->rlink = newStudent;
        }
        else if (next == NULL && pre != NULL) {
            newStudent->llink = pre;
            pre->rlink = newStudent;
            DL->last = newStudent;
        }
        else if (next != NULL && pre == NULL) {
            newStudent->rlink = next;
            next->llink = newStudent;
            DL->start = newStudent;
        }
    }
}

void deleteStudent(line_up* DL, student* out) {     //��� ����
    if (DL->start == NULL)
        return;
    else if (out == NULL)
        return;
    else {

        if (out->llink == NULL && out->rlink == NULL) {
            DL->start = NULL;
            DL->last = NULL;
            free(out);
            return;
        }
        if (out->llink == NULL) {
            DL->start = out->rlink;
            DL->start->llink = NULL;
            free(out);
        }
        else if (out->rlink == NULL) {
            DL->last = out->llink;
            DL->last->rlink = NULL;
            free(out);
        }
        else {
            out->llink->rlink = out->rlink;
            out->rlink->llink = out->llink;
            free(out);
        }
    }
}

student* searchNextHeight(line_up* DL, double h) {  //Ű�� ���� ����ƮŽ��(���� ���)
    student* temp;
    temp = DL->start;
    while (temp != NULL) {
        if (h <= temp->height)
            return temp;
        else
            temp = temp->rlink;
    }
    return temp;
}

student* searchPreHeight(student* s, line_up* DL) { //Ű�� ���� ����Ʈ Ž��(���� ���)
    if (s == NULL) return DL->last;
    else {
        if (s->llink == NULL) return NULL;
        else if (s->llink != NULL) {
            return s->llink;
        }
        else return NULL;
    }
}

student* searchName(line_up* DL, char* name) {  //�̸� ã��
    student* temp;
    temp = DL->start;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0)
            return temp;
        else
            temp = temp->rlink;
    }
    return temp;
}

int main() {
    int num;
    double height;
    char name[50];
    line_up* DL;
    student* next;

    DL = createLine_up();
    while (1) {
        printf("0: ����\n");
        printf("1: �л� �߰�\n");
        printf("2: �л� ����\n");
        printf("3: �������� ���\n");
        printf("4: �������� ���\n");
        scanf("%d", &num);
        if (num == 0)
            break;
        else if (num == 1) {
            printf("�л��� �̸��� �Է��ϼ���: ");
            scanf(" %s", name);
            printf("�л��� Ű�� �Է��ϼ���: ");
            scanf("%lf", &height);
            next = searchNextHeight(DL, height);
            student* pre = searchPreHeight(next, DL);
            insertStudent(DL, pre, next, name, height);
        }
        else if (num == 2) {
            printf("�л��� �̸��� �Է��ϼ���: ");
            scanf(" %s", name);
            student* p = searchName(DL, name);
            deleteStudent(DL, p);
        }
        else if (num == 3)
            print(DL);
        else if (num == 4)
            reverseprint(DL);
    }
    return 0;
}