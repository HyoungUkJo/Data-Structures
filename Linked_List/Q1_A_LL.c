//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////
// 연결리스트의 노드의 구조는 아템과 다음 노드를 가리키는 포인터로 구성이됨
typedef struct _listnode{
    int item;
    struct _listnode *next;
} ListNode;         // You should not change the definition of ListNode
// 연결 리스트는 이런 노드의 집합으로 노드의 갯수와 노드의 헤드를 가리키게 된다. 헤드를 가리키면 연쇄적으로 찾을 수 있게 되는듯
typedef struct _linkedlist{
    int size;
    ListNode *head;
} LinkedList;           // You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
    LinkedList ll;
    int c, i, j;
    c = 1;

    //Initialize the linked list 1 as an empty linked list
    ll.head = NULL;
    ll.size = 0;

    printf("1: Insert an integer to the sorted linked list:\n");
    printf("2: Print the index of the most recent input value:\n");
    printf("3: Print sorted linked list:\n");
    printf("0: Quit:");

    while (c != 0)
    {
        printf("\nPlease input your choice(1/2/3/0): ");
        scanf("%d", &c);

        switch (c)
        {
        case 1:
            printf("Input an integer that you want to add to the linked list: ");
            scanf("%d", &i);
            j = insertSortedLL(&ll, i);
            printf("The resulting linked list is: ");
            printList(&ll);
            break;
        case 2:
            printf("The value %d was added at index %d\n", i, j);
            break;
        case 3:
            printf("The resulting sorted linked list is: ");
            printList(&ll);
            // removeAllItems(&ll);
            break;
        case 0:
            removeAllItems(&ll);
            break;
        default:
            printf("Choice unknown;\n");
            break;
        }


    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{
    // 연결리스트 전체가 주어짐. 새로은 item 이들어오면 정렬함.
    // 메모리도 할당 해줘야할듯
    // 리스트가 비워져있을 경우도 생각을 해야함.
    /* add your code here */
    //먼저 리스트들을 순회 하자.
    ListNode *cur; // 현재 노드 저장
    ListNode *pre; // 전 노드 주소 저장
    int index = 1;
    //초기 노드를 탐색하기 위해 해드를 맞추어준다.
    pre = ll->head;
    //만약 head가 아무것도 가리키고 있지 않을 경우에는 비워져있는것임으로 노드를 추가시킨다.
    if(pre==NULL||pre->item>item) {
        ll->head = malloc(sizeof(ListNode)); // 새로 할당한 메모리 주소를 리스트의 헤드에 저장
        ll->head->item = item; //노드에 아이템 삽입
        ll->head->next = NULL; // 다음값은 없음으로 Null
        ll->size++; //리스트의 크기 증가.
        return 0;
    }
    while(pre->next!=NULL && pre->next->item<item){
        pre=pre->next;
        index++;
    }
    if(pre ->next !=NULL && pre->next->item==item){
        return -1;
    }
    
    cur = pre->next;
    cur = malloc(sizeof(ListNode));
    cur->next = pre->next;
    pre->next = cur;
    cur->item = item;

    return index;
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

    ListNode *cur;
    if (ll == NULL)
        return;
    cur = ll->head;

    if (cur == NULL)
        printf("Empty");
    while (cur != NULL)
    {
        printf("%d ", cur->item);
        cur = cur->next;
    }
    printf("\n");
}


void removeAllItems(LinkedList *ll)
{
    ListNode *cur = ll->head;
    ListNode *tmp;

    while (cur != NULL){
        tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    ll->head = NULL;
    ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

    ListNode *temp;

    if (ll == NULL || index < 0 || index >= ll->size)
        return NULL;

    temp = ll->head;

    if (temp == NULL || index < 0)
        return NULL;

    while (index > 0){
        temp = temp->next;
        if (temp == NULL)
            return NULL;
        index--;
    }

    return temp;
}

int insertNode(LinkedList *ll, int index, int value){

    ListNode *pre, *cur;

    if (ll == NULL || index < 0 || index > ll->size + 1)
        return -1;

    // If empty list or inserting first node, need to update head pointer
    if (ll->head == NULL || index == 0){
        cur = ll->head;
        ll->head = malloc(sizeof(ListNode));
        ll->head->item = value;
        ll->head->next = cur;
        ll->size++;
        return 0;
    }


    // Find the nodes before and at the target position
    // Create a new node and reconnect the links
    if ((pre = findNode(ll, index - 1)) != NULL){
        cur = pre->next;
        pre->next = malloc(sizeof(ListNode));
        pre->next->item = value;
        pre->next->next = cur;
        ll->size++;
        return 0;
    }

    return -1;
}


int removeNode(LinkedList *ll, int index){

    ListNode *pre, *cur;

    // Highest index we can remove is size-1
    if (ll == NULL || index < 0 || index >= ll->size)
        return -1;

    // If removing first node, need to update head pointer
    if (index == 0){
        cur = ll->head->next;
        free(ll->head);
        ll->head = cur;
        ll->size--;

        return 0;
    }

    // Find the nodes before and after the target position
    // Free the target node and reconnect the links
    if ((pre = findNode(ll, index - 1)) != NULL){

        if (pre->next == NULL)
            return -1;

        cur = pre->next;
        pre->next = cur->next;
        free(cur);
        ll->size--;
        return 0;
    }

    return -1;
}

