#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
printf("안녕");
 typedef struct Student {    //이중연결리스트
    struct Student* llink;  //왼쪽노드에 대한 링크
    double height;          //키
    char name[50];          //이름
    struct Student* rlink;  //오른쪽 노드에 대한 링크
}student;

typedef struct {
    student* start; //리스트시작
    student* last;  //리스트끝
}line_up;

line_up* createLine_up(void) {  //공백 이중연결리스트 생성
    line_up* DL;
    DL = (line_up*)malloc(sizeof(line_up));
    DL->start = NULL;
    DL->last = NULL;
    return DL;
}

void print(line_up* DL) {   //리스트를 순서대로 출력(오름차순)
    student* p;
    p = DL->start;
    if (DL->start == NULL)
        printf("비어있는 명단입니다.\n");
    else {
        while (p != NULL) {
            printf("%s  (%.0f)\n", p->name, p->height);
            p = p->rlink;
        }
    }
}

void reverseprint(line_up* DL) {    //리스트를 뒤에서부터 출력(내림차순)
    student* p;
    p = DL->last;
    if (DL->start == NULL)
        printf("비어있는 명단입니다.\n");
    else {
        while (p != NULL) {
            printf("%s  (%.0f)\n", p->name, p->height);
            p = p->llink;
        }
    }
}
void insertStudent(line_up* DL, student* pre, student* next, char* x, double h) {   //노드 삽입
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

void deleteStudent(line_up* DL, student* out) {     //노드 삭제
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

student* searchNextHeight(line_up* DL, double h) {  //키를 보고 리스트탐색(다음 노드)
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

student* searchPreHeight(student* s, line_up* DL) { //키를 보고 리스트 탐색(이전 노드)
    if (s == NULL) return DL->last;
    else {
        if (s->llink == NULL) return NULL;
        else if (s->llink != NULL) {
            return s->llink;
        }
        else return NULL;
    }
}

student* searchName(line_up* DL, char* name) {  //이름 찾기
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
        printf("0: 종료\n");
        printf("1: 학생 추가\n");
        printf("2: 학생 삭제\n");
        printf("3: 오름차순 출력\n");
        printf("4: 내림차순 출력\n");
        scanf("%d", &num);
        if (num == 0)
            break;
        else if (num == 1) {
            printf("학생의 이름을 입력하세요: ");
            scanf(" %s", name);
            printf("학생의 키를 입력하세요: ");
            scanf("%lf", &height);
            next = searchNextHeight(DL, height);
            student* pre = searchPreHeight(next, DL);
            insertStudent(DL, pre, next, name, height);
        }
        else if (num == 2) {
            printf("학생의 이름을 입력하세요: ");
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