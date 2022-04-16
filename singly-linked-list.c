#include <stdio.h>
#include <Stdlib.h>

typedef struct Node
{
	int key;
	struct Node *link;
} listNode;

typedef struct Head
{
	struct Node *first;
} headNode;

headNode *initialize(headNode *h);
int freeList(headNode *h);

int insertFirst(headNode *h, int key);
int insertNode(headNode *h, int key);
int insertLast(headNode *h, int key);

int deleteFirst(headNode *h);
int deleteNode(headNode *h, int key);
int deleteLast(headNode *h);
int invertList(headNode *h);

void printList(headNode *h);

int main()
{
	char command;
	int key;
	headNode *headnode = NULL;

	printf("--------------[hankyuwon]------------[2019037002]---------------\n");
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
{ // headnode 에 대한 메모리를 할당
	if (h != NULL) // 연결 리스트의 시작과 같은 headNode가 NULL이 아닐 경우, freeNode를 통해 할당된 메모리 모두 해제
		freeList(h);

	headNode *temp = (headNode *)malloc(sizeof(headNode)); //headNode 에 대한 메모리 할당. headNode 의 첫 생성이므로 first가 가리키는 값은 NULL
	temp->first = NULL;
	return temp;
}

int freeList(headNode *h)
{ // list 메모리 해제, headnode도 해제되어야 함.
	listNode *p = h->first; // Head 다음, listNode의 첫 부분으로 listNode *p 정의

	listNode *prev = NULL;
	while (p != NULL) // p부터 p->link 해가면서 메모리 해제
	{
		prev = p; // free(p); p=p->link; 가 안되므로 prev를 이용하여 하나씩 메모리 해제
		p = p->link;
		free(prev);
	}
	free(h); // Head 부분의 h 메모리 해제
	return 0;
}

int insertNode(headNode *h, int key)
{ //리스트를 검색하여, 입력받은 key보다 큰 값이 나오는 노드 바로 앞에 삽입
	listNode *node = (listNode *)malloc(sizeof(listNode)); // 입력받은 key와 lilnk를 담을 listNode *node 메모리 할당
	node->key = key;
	node->link = NULL;

	if (h->first == NULL) // h->first = NULL 인 경우 listNode가 비어있다는 의미이므로 바로 h->first = node;
	{
		h->first = node;
		return 0;
	}

	listNode *n = h->first; // listNode가 비어있지 않은 경우 Head 바로 뒤인 listNode *n을 정의하여 key값을 비교
	listNode *trail = h->first; 

	while (n != NULL) // n이 NULL을 가리킬때까지 > 연결 리스트의 끝부분까지 (연결리스트의 마지막은 NULL을 가리킴)
	{
		if (n->key >= key) // key 값 비교
		{
			if (n == h->first) // n이 listNode의 첫 부분일때
			{
				h->first = node; // Head와 n 사이에 node를 끼워줌
				node->link = n;
			}
			else // n이 listNode의 첫 부분이 아닐 때
			{
				node->link = n; // trail와 n사이에 node를 끼워줌
				trail->link = node;
			}
			return 0;
		}

		trail = n; // 입력받은 key값이 n->key 값보다 클 때 trail을 n으로 두고 
		n = n->link; // n 을 다음 n값으로 이동시키면서 비교
	}

	trail->link = node; // n이 NULL일 때까지 비교했음에도 불구하고 입력받은 key값이 trail->key 값보다 클때 trail 뒤에 node를 붙힘
	return 0;
}

int insertLast(headNode *h, int key)
{ // list에서 key에 대한 노드 마지막에 추가
	listNode *node = (listNode *)malloc(sizeof(listNode)); // 입력받은 key와 link를 담을 linkNode *node 메모리 할당
	node->key = key;
	node->link = NULL; // 마지막에 추가이므로 node->link는 자동적으로 NULL을 가리킴

	if (h->first == NULL) // listNode가 비어있을 경우
	{
		h->first = node; // h->first, 즉 listNode의 첫 부분에 node 이어붙힘
		return 0;
	}

	listNode *n = h->first; // listNode가 비어있지 않은 경우
	while (n->link != NULL) // n->link가 NULL을 가리킬 때, 즉 listNode의 마지막부분을 찾음
	{
		n = n->link;
	}
	n->link = node; // listNode 의 마지막 부분인 n->link 뒤에 node를 이어붙힘
	return 0;
}

int insertFirst(headNode *h, int key)
{ // list 처음에 key에 대한 노드 추가

	listNode *node = (listNode *)malloc(sizeof(listNode)); // 입력받은 key와 link를 담을 linkNode *node 메모리 할당
	node->key = key;

	node->link = h->first; // Head와 h->first 사이에 node 추가
	h->first = node;

	return 0;
}

int deleteNode(headNode *h, int key)
{ // list에서 key에 대한 노드 삭제
	if (h->first == NULL) // listNode가 비어있을시
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode *n = h->first; // Head 다음, 즉 listNode의 첫 부분 n으로 정의
	listNode *trail = NULL;

	while (n != NULL) // listNode의 마지막 부분까지 반복
	{
		if (n->key == key) // n->key 값과 입력받은 key 값이 같은 경우
		{
			if (n == h->first) // listNode의 첫 부분일 경우
			{
				h->first = n->link; // h->first = n->link로 n 삭제
			}
			else // listNode의 첫 부분이 아닐 경우
			{
				trail->link = n->link; // trail->link = n->link 로 n 삭제
			}
			free(n); // 삭제 이후 메모리 해제
			return 0;
		}

		trail = n; // n->key 값과 입력받은 key값이 다른경우 trail을 n으로 두고
		n = n->link; // n=n->link로 다음 n으로 넘어감
	}

	printf("cannot find the node for key = %d\n", key); // listNode의 마지막 부분까지 찾지 못했다면 cannot
	return 0;
}

int deleteLast(headNode *h)
{ // list의 마지막 노드 삭제

	if (h->first == NULL) // listNode가 비어있는지 확인
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode *n = h->first;
	listNode *trail = NULL;

	if (n->link == NULL) // listNode에 하나의 노드만 있을 경우
	{
		h->first = NULL; // n 삭제 이후 메모리 해제
		free(n);
		return 0;
	}

	while (n->link != NULL) // listNode에 두개 이상의 노드가 있을 경우 listNode의 마지막 부분까지
	{
		trail = n; // trail을 n으로 두고 n=n->link 로 listNode의 마지막을 찾음
		n = n->link;
	}
	trail->link = NULL; // n->NULL 을 가리키는 경우까지 찾은 이후 trail을 마지막 노드로 설정하고 n은 메모리 해제
	free(n);

	return 0;
}

int deleteFirst(headNode *h)
{ // list의 첫 번째 노드 삭제
	if (h->first == NULL) // listNode가 비어있는 경우
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode *n = h->first; // listNode의 첫번째부분 n으로 정의

	h->first = n->link; // h->first = n->link로 n 삭제
	free(n); // n에 대한 메모리 해제

	return 0;
}

int invertList(headNode *h)
{ //리스트의 링크 역순으로 재 배치
	if (h->first == NULL) // listNode가 비어있는 경우
	{
		printf("nothing to invert...\n");
		return 0;
	}

	listNode *n = h->first; // listNode를 역순으로 배치하기 위해서 middle, 이전의 node를 기억할 trail, 다음 node를 가리킬 n 세개의 listNode 정의
	listNode *trail = NULL;
	listNode *middle = NULL;

	while (n != NULL)
	{
		trail = middle; 
		middle = n;
		n = n->link; // n=n->link 로 마지막 node까지 n 증가
		middle->link = trail; // middle->link는 trail을 가리키며 n이 하나씩 증가하면서 지나온 node들은 이전 node를 가리키게됨
	}

	h->first = middle; // 역순이므로 h->first도 바뀌어야 한다. 현재 listNode의 첫부분은 middle 이므로 h->first = middle

	return 0;
}

void printList(headNode *h)
{ // 연결 리스트 출력
	int i = 0; // node의 번호를 매겨주기 위해 i 정의
	listNode *p;

	printf("\n---PRINT\n");

	if (h->first==NULL) // h->first == NULL 로 수정
	{
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; // listNode의 첫 부분 p

	while (p != NULL) // listNode의 마지막 부분까지 p=p->link로 증가시키며 출력
	{
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++; // p를 증가시킨만큼 i도 증가시켜 몇개의 node가 있는지 출력
	}

	printf("  items = %d\n", i);
}