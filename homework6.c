/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

	printf("[----- [정세연] [2018038027] -----]\n");

	do {
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
		fflush(stdout);
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; // p는 헤더노드가 가리키는 노드이다.

	listNode* prev = NULL;
	while (p != NULL) {//노드가 NULL이 아닐 때까지(가장 마지막 노드까지)
		prev = p; // p의 이전노드를 prev에 저장
		p = p->link; //p가 가리키는 노드를 p로 바꿔준다.
		free(prev);//이전 노드를 해제
	}
	free(h); //헤더노드를 해제시킴
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 동적할당을 이용하여 노드 생성
	node->key = key; // 노드의 key값에 매개변수로 받은 key값을 대입

	node->link = h->first; // node 노드가 헤더노드가 가리키는 노드를 가리키게함
	h->first = node; // 헤더노드가 node를 가리키게함

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key)
{
	listNode* cur = h->first;//탐색을 위해 cur이라는 노드를 가리키는 포인터를 생성하고 리스트의 first를 가리키게함
	listNode* stocur = NULL; // cur의 이전 노드를 기억하는 노드를 가리키는 포인터를 생성
	listNode* n1 = (listNode*)malloc(sizeof(listNode));//동적할당을 이용하여 n1노드를 생성
	n1->key = key; // n1노드의 key값에 매개변수로 받은 key값을 대입

	if (h->first == NULL) //만약 헤더노드가 가리키는 노드가 NULL이라면(노드가 없음)
	{
		h->first = n1; // 헤더노드가 n1노드를 가리키게하고
		n1->link = NULL; // n1이 NULL을 가리키게함 (n1을 첫번째 노드로 설정해줌)
		return 0;
	}
	else if (h->first->key >= n1->key) //헤더노드가 가리키는 노드의 key 값이 n1의 key값보다 크거나 같은경우
	{

		n1->link = h->first; // n1이 가리키는 값이 헤더노드가 가리키는 노드가됨.
		h->first = n1; // 헤더노드가 가리키는 값이 n1노드가 됨.
		return 0;
	}

	while (cur != NULL)//cur이 NULL일때까지 반복
	{
		if (cur->key > n1->key) // 만약 cur의 key값이 n1의 key값보다 큰경우
		{

			n1->link = cur; //n1노드가 가리키는 노드가 cur이됨.
			stocur->link = n1; //n1노드가 가리키는 노드가 cur이됨.
			return 0;
		}
		if (cur->key == n1->key) // 만약 cur의 key값이 n1의 key 값과 같은경우
		{

			n1->link = cur; //n1노드가 가리키는 노드가 cur이됨.
			stocur->link = n1; //n1노드가 가리키는 노드가 cur이됨.
			return 0;
		}


		stocur = cur; //위의 두 if문의 조건에 만족하지 않는다면 cur노드를 이전노드로 설정
		cur = cur->link; //cur노드를 cur이 가리키던 노드로 설정


	}
	n1->link = cur; // cur이 NULL이라면 (끝까지 탐색했을 경우이므로 n1의 key값이 가장 큰값!) n1이 가리키는 값이 cur 즉, NULL 즉, 마지막 노드가 된다.
	stocur->link = n1; // cur의 이전값이 가리키는 노드가 n1이 됨.



	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {




	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h)
{



	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key)
{

	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h)
{



	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {



	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}
