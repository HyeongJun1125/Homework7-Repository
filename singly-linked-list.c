/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science
 *  at Chungbuk National University
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* �ʿ��� ������� �߰� */

typedef struct Node
{
    int key;
    struct Node *link;
} listNode;

typedef struct Head
{
    struct Node *first;
} headNode;

/* �Լ� ����Ʈ */
headNode *initialize(headNode *h);
int freeList(headNode *h);

int insertFirst(headNode *h, int key); // �Ӹ��� ����ֱ�
int insertNode(headNode *h, int key);  // ������� ���� ���¿��� ���̿� �����ֱ�
int insertLast(headNode *h, int key);  // ������ �κп� �����ϱ�

int deleteFirst(headNode *h);         // head�� ����Ű�� ��� ����
int deleteNode(headNode *h, int key); // �߰��� �� ��� ����
int deleteLast(headNode *h);          // ������ ��� ����
int invertList(headNode *h);          // ����Ʈ ���� ������

void printList(headNode *h); // ��ü ����� ���

int main()
{
    printf("\n2021041069 ������\n");
    char command;
    int key;
    headNode *headnode = NULL;

    /*while���� �� ��� �Է¹��� �Ŀ� �����ϸ鼭
    �ɸ��� ������ ���๮�� ���� ���ϰ� ��.*/
    // do while���� �� ��� while���� ���������� �ɸ��Ƿ�
    // �ּ� 1���� �ʱ� ������ ������.

    do
    {
        printf("----------------------------------------------------------------\n");
        printf("                     Singly Linked List                         \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize    = z           Print         = p \n");
        printf(" Insert Node   = i           Delete Node   = d \n");
        printf(" Insert Last   = n           Delete Last   = e\n");
        printf(" Insert First  = f           Delete First  = t\n");
        printf(" Invert List   = r           Quit          = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command)
        {
        case 'z':
        case 'Z':
            headnode = initialize(headnode);
            break;
        case 'p':
        case 'P':
            printList(headnode);
            break;
        case 'i':
        case 'I':
            printf("Your Key = ");
            scanf("%d", &key);
            insertNode(headnode, key);
            break;
        case 'd':
        case 'D':
            printf("Your Key = ");
            scanf("%d", &key);
            deleteNode(headnode, key);
            break;
        case 'n':
        case 'N':
            printf("Your Key = ");
            scanf("%d", &key);
            insertLast(headnode, key);
            break;
        case 'e':
        case 'E':
            deleteLast(headnode);
            break;
        case 'f':
        case 'F':
            printf("Your Key = ");
            scanf("%d", &key);
            insertFirst(headnode, key);
            break;
        case 't':
        case 'T':
            deleteFirst(headnode);
            break;
        case 'r':
        case 'R':
            invertList(headnode);
            break;
        case 'q':
        case 'Q':
            freeList(headnode);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

headNode *initialize(headNode *h)
{

    /* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
    if (h != NULL)
        freeList(h);

    /* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
    headNode *temp = (headNode *)malloc(sizeof(headNode));
    temp->first = NULL;
    return temp;
    // h�� �����������Ƿ� �߰������� malloc�� ���� �޸� �Ҵ�����
    // �Լ��� return���� ��ȯ����.
}

int freeList(headNode *h)
{
    /* h�� ����� listNode �޸� ����
     * headNode�� �����Ǿ�� ��.
     */
    listNode *p = h->first; // ������ ������ p�� head�� ����Ű�� ��.

    listNode *prev = NULL; // p�� ���� ���� �����Ƿ� NULL���� ����.
    while (p != NULL)
    {
        prev = p;    // ���� ���� prev�� �ְ�
        p = p->link; // p�� �ϳ��� �ǳʰ��鼭
        free(prev);  // prev���� ��� ���������ش�.
    }
    free(h); // �۾��� ��� ������ head�� �޸� ����.
    return 0;
}

/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
// ���ʿ� �ϳ� �߰�.
int insertFirst(headNode *h, int key)
{
    // �Ӹ��� �ʱ� ����Ʈ head���� �־��ֱ�.
    listNode *node = (listNode *)malloc(sizeof(listNode)); // �߰��� ��� ����.
    node->key = key;                                       // �Ű����� key���� ����� key���� ����.

    node->link = h->first; // node�� next �����Ͱ� head->first�� ����Ű�� ���� head���� ����Ŵ.
    h->first = node;       // head�� ����Ű�� ���� �߰��� ���� �Ű���.

    return 0;
}

/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
// ���� Case ������ �� ��¥ ��������........�Ф�
int insertNode(headNode *h, int key)
{ // listNode : int key, *link

    // first ��庸�� ū ���, ���� ��� 2���� Case
    listNode *node = (listNode *)malloc(sizeof(listNode));
    node->key = key;
    node->link = NULL;
    listNode *p = h->first;

    // Case 1 : head�� ����ų� head���� ���� �۴ٸ�
    if (h->first == NULL || key < p->key)
    { // head�� �߰��ϰ� head�� �߰��� ���ο� ��带 ����Ű�� ��.
        insertFirst(h, key);
        return;
    }

    // Case 2 : �߰��� �����
    while (p->link != NULL && p->link->key < key) // ������ ���, �Ǵ� �߰��� ����� ��쿡�� Ż��.
        p = p->link;

    // �ٽ� ������ ������ �� ���, �߰��� ����� ���� Case ����.

    // Case 2-1 : �߰��� ����� ��� (p->link, �� p�� ���������ٴ� key���� ���� ���)
    node->link = p->link; //
    p->link = node;
    // node�� ���� ���� ������ p�� link������ ���� �Ǹ�
    // ���� p->link���� �ҽǵ�.

    // Case 2-2 : ������ ����� ���
    if (p->link == NULL)
    {
        insertLast(h, key); // �������� ����.
        return;
    }

    return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode *h, int key)
{
    // ������ ��忡���� ��
    // ���������� ������ ��庸�� Ŭ ���, ���� ��� 2 Case.
    listNode *node = (listNode *)malloc(sizeof(listNode));
    node->key = key;
    node->link = NULL;

    listNode *p = h->first;
    while (p->link != NULL) // ������ ������ �̵�.
        p = p->link;        // p���� ������ ����� ������ ��� �ǳʰ�.

    p->link = node; // ������ ��� �ٷ� �ڿ� ����.
    return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode *h)
{
    listNode *p = h->first; // ������ p�� head��带 ����Ű���� ����.
    if (p == NULL)
        return;

    h->first = p->link; // head�� ����Ű�� ���� head->next�� �Ű���.
    free(p);            // �׸��� p�� ����Ű�� head first�� �޸� ����.
    return 0;
}

/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode *h, int key)
{
    listNode *p = h->first; // ���� ����Ű�� ���� first���
    listNode *prev = NULL;

    // Case 1 : head�� �ִ� ��带 �����ϴ� ���
    // ������� �����鼭 first�� key�� key�� ��ġ�Ѵٸ�
    if (h->first != NULL && h->first->key == key)
    {
        deleteFirst(h);
        return;
    }

    // Case 2 : Head �ڿ� �ִ� ��带 �����ϴ� ���

    while (p != NULL && p->key != key) // ������ ������ ���� ���߰ų� �� ���� key���� ã�� ��� Ż��.
    {
        prev = p;
        p = p->link;
    }

    // Case 2-1 : �߰��� ���� ��带 �����ϴ� ���
    prev->link = p->link;
    free(p);

    // Case 2-2 : ������ ����̸鼭 key���� ��ġ�ϴ� ���
    if (p->key == NULL)
    {
        deleteLast(h);
        return;
    }

    // Case 2-3 : ������ ���Ҵµ��� key ���� �������� ������
    if (p == NULL)
        return;

    return 0;
}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode *h)
{
    listNode *p = h->first;
    listNode *prev = NULL;
    while (p->link != NULL) // p�� ������ ��带 ����Ű�� Ż��.
    {
        prev = p;
        p = p->link; // p���� ������ ����� ������ ��� �ǳʰ�.
    }
    prev->link = NULL; // p�� ������ ������ �޸� ����.
    free(p);           // ������ ��带 ����Ű�� p �����͸� ����������.
    return 0;
}

/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode *h) // 3���� �����͸� �̿��� ���� Cycle �����.
{
    // ������, ���簪, �������� �޾��ִ� 3���� �����͸� ���.
    // Why? ����ؼ� ���ӵ� ������ �޾���� 1���� ���� Cycle�� ���� �� ����.
    listNode *prev = NULL;
    listNode *p = h->first;
    listNode *next = NULL;

    while (p != NULL)
    {
        next = p->link;
        p->link = prev;
        // ������� 1 Cycle

        prev = p;
        p = next;
        // prev, p�� ��ĭ�� ������.
    }
    // p�� NULL�� �Ǹ鼭 Ż�������μ� ����� ��������
    // prev ������ ��� �������� ������ �� ����.
    // ���� ����� �������� prev���� head�� ����Ű�� ��.
    h->first = prev;
    return 0;
}

void printList(headNode *h)
{
    int i = 0;
    listNode *p = h->first;

    printf("\n---PRINT\n");

    if (h == NULL)
    {
        printf("Nothing to print....\n");
        return;
    }

    while (p != NULL)
    {
        printf("[ [%d]=%d ] ", i, p->key);
        p = p->link;
        i++;
    }

    printf("  items = %d\n", i);
}