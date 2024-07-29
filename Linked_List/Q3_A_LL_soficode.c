//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 3 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void moveOddItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
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


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all odd integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveOddItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving odd integers to the back of the linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
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

void moveOddItemsToBack(LinkedList *ll)
{
	ListNode *previous_node;
	ListNode *current_node;
	ListNode *index_node;
	LinkedList odd_list = {0, NULL};

	int index = 0;
	int odd_count = 0;

	/* add your code here */
	if (ll == NULL || ll->size == 0) {
		printf("노드가 존재하지 않습니다.\n");
		return;
	}

	previous_node = ll->head;
	current_node = ll->head;
	while (current_node != NULL)  {
		int item = current_node->item;

		if (item % 2 != 0) {
			/* 1. 홀수일 경우 odd_nodes에 insert합니다. */
			insertNode(&odd_list, odd_list.size, item);

			/* 2. 홀수 개수가 전체 사이즈와 동일하면 종료해줍니다. */
			odd_count++;
			if (odd_count == ll->size) {
				ll->head = odd_list.head;
				return;
			}

			/* 3. 기존 노드가 다음으로 가르키고 있는 주소를 해당 노드의 다음주소로 변경해줍니다. */
			if (index == 0) {
				ll->head = current_node->next;
			} else {
				/* 이전노드의 다음노드 주소를 변경해줍니다. */
				previous_node->next = current_node->next;
			}
		} else {
			previous_node = current_node;
		}
		current_node = current_node->next;
		index++;
	}
	previous_node->next = odd_list.head;


	// ListNode *pre_node, *cur_node;

	// // 홀수만 저장할 리스트를 생성
    // LinkedList *tmp_ll = (LinkedList *)malloc(sizeof(LinkedList));
    // if (tmp_ll == NULL) {
    //     // 메모리 할당 실패 처리
    //     return;
    // }
    // tmp_ll->head = NULL;
    // tmp_ll->size = 0;

    // ListNode *tmp_node = NULL;
	// pre_node = ll->head;
	// cur_node = pre_node;
	// // tmp_ll->head = tmp_ll_node;
	// while (cur_node != NULL){
	// 	if((ll->head->item)%2==1){
	// 		cur_node = ll->head;
	// 		ll->head = cur_node->next;
	// 		if (tmp_ll->head == NULL){
	// 			tmp_ll->head = cur_node;
	// 			tmp_node = tmp_ll->head;
	// 		}
	// 		else {
	// 			tmp_node->next = cur_node;
	// 			tmp_node= tmp_node->next;
	// 		}
	// 	}

	// 	if((cur_node -> item)%2==0){
	// 		pre_node = cur_node;
	// 		cur_node=cur_node->next;
	// 	}
	// 	else {
	// 		pre_node->next = cur_node->next;
	// 		cur_node->next = NULL;
	// 		if (tmp_ll->head == NULL){
	// 			tmp_ll->head = cur_node;
	// 			tmp_node = tmp_ll->head;
	// 		}
	// 		else {
	// 			tmp_node->next = cur_node;
	// 			tmp_node= tmp_node->next;
	// 		}
	// 	}
	// 	cur_node = pre_node->next;
	// }
	// pre_node->next = tmp_ll->head;
	// free(tmp_ll);
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
