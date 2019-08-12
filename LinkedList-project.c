#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node* next;
};

typedef struct poly{
	int coeff;
	int power;
	struct poly* next;
}poly;

void dispoly();

struct node* head = NULL;
poly* phead1 = NULL;
poly* phead2 = NULL;
poly* result = NULL;

void polycreate(){
	int n, i = 0;
	printf("enter degree of the polynomial 1 : ");
	scanf("%d", &n);
	while(n >= 0){
		poly* temp = (poly*)malloc(sizeof(poly));
		printf("enter coefficient of x^%d: ", n);
		temp->power = n;
		scanf("%d", &temp->coeff);
		printf("\n");
		temp->next = NULL;
		if(phead1 == NULL)	phead1 = temp;
		else{
			poly* ptr = phead1;
			while(ptr->next != NULL)
					ptr = ptr->next;
			ptr->next = temp;
		}
		n--;
	}

	printf("enter degree of the polynomial 2 : ");
	scanf("%d", &n);
	while(n >= 0){
		poly* temp = (poly*)malloc(sizeof(poly));
		printf("enter coefficient of x^%d: ", n);
		temp->power = n;
		scanf("%d", &temp->coeff);
		printf("\n");
		temp->next = NULL;
		if(phead2 == NULL)	phead2 = temp;
		else{	
			poly* ptr = phead2;
			while(ptr->next != NULL)
				ptr = ptr->next; 
			ptr->next = temp;
		}
		n--;
	}
	printf("\n");
}

void dispoly(){
	poly* temp1 = phead1;
	poly* temp2 = phead2;
	printf("\t\t\t\t\t\t\t");
	while(temp1->next != NULL){
		printf("%dX^%d + ", temp1->coeff, temp1->power);
		temp1 = temp1->next;
	}
	printf("%d", temp1->coeff);
	printf("\n");
  printf("\t\t\t\t\t\t\t");
	while(temp2->next != NULL){
		printf("%dX^%d + ", temp2->coeff, temp2->power);
		temp2 = temp2->next;
	}
	printf("%d\n", temp2->coeff);
}

void polyadd(){
	poly* temp;
	poly* temp1;
	if(phead1->power > phead2->power){
		temp = phead1;
		temp1 = phead2;
	}
	else if(phead1->power < phead2->power){
		temp = phead2;
		temp1 = phead1;
	}
  printf("\t\t\t\t\t\t\t");
	while(temp->power != temp1->power){	
		printf("%dX^%d + ", temp->coeff, temp->power);
		temp = temp->next;
	}
	while(temp->next != NULL && temp1->next != NULL){
		printf("%dX^%d + ", temp->coeff +  temp1->coeff, temp->power);
		temp = temp->next;
		temp1 = temp1->next;
	}
	printf("%d\n", temp->coeff +  temp1->coeff);
}

void final(){
	poly* temp = result;
	poly* temp1 = temp->next;
	while(temp->next != NULL){
		if(temp->power == temp1->power){
			temp->coeff += temp1->coeff;
			temp->next = temp1->next;
			temp1 = temp->next;
		}
		else{	temp = temp->next;	temp1 = temp->next;}
	}
	temp = result;
	printf("\t\t\t\t\t\t\t");
	while(temp->next != NULL){
		printf("%dX^%d + ", temp->coeff, temp->power);
		temp = temp->next;
	}
	printf("%d\n", temp->coeff);
}

void polyswap(poly* a, poly* b){
  int temp = a->coeff;
  a->coeff = b->coeff;
  b->coeff = temp;

	temp = a->power;
	a->power = b->power;
	b->power = temp;
}

void polyselsort(){
  int n = 0;
  poly* temp = result;
  poly* i = result;
  poly* j;
  poly* min;
  while(i != NULL){
    min = i;
    j = i->next;
    while(j != NULL){
      if(j->power > min->power)
        min = j;
      j = j->next;
    }
    if(min->power > i->power)
      polyswap(min, i);
    i = i->next;
  }
}

void polymultiply(){
	poly* temp1 = phead1;
	poly* temp2 = phead2;
	while(temp1 != NULL){
		while(temp2 != NULL){
			poly* temp = (poly*)malloc(sizeof(poly));
			temp->coeff = temp1->coeff * temp2->coeff;
			temp->power = temp1->power + temp2->power;
			temp->next = NULL;
			if(result == NULL)
				result = temp;
			else{
				poly* ptr = result;
				while(ptr->next != NULL)	ptr = ptr->next;
				ptr->next = temp;
			}
			temp2 = temp2->next;
		}
		temp2 = phead2;
		temp1 = temp1->next;
	}
	polyselsort();
	final();
}

void polyinitiate(){
	polycreate();
	dispoly();
	int n;
	int ch  = 1;
	printf("\n1) Add polynomials\n2) Multiply polynomials\n3) Create new polynomials\n4) Show menu\n0) exit to main menu");
	while(ch){
		printf("\n");
		scanf("%d", &n);
		switch(n){
			case 1:	{	polyadd();	break;}
			case 2: {	polymultiply();	break;}
			case 3:	{	result = NULL; phead1 = NULL; phead2 = NULL; polycreate(); dispoly();	break;}
			case 4: {	printf("\n1) Add polynomials\n2) Multiply polynomials\n3) Create new polynomials\n4) Show menu\n0) exit to main menu");	break;}
			case 0: {	result = NULL; phead1 = NULL; phead2 = NULL; ch = 0;}
		}
	}
}

void evenodd(){
	struct node* temp = head;
	printf("odd elements : ");
	while(temp != NULL){
		if((temp->data) & 1)	printf("%d ", temp->data);
		temp = temp->next;
	}
	temp = head;
	printf("\neven elements : ");
	while(temp != NULL){
		if(!((temp->data) & 1))	printf("%d ", temp->data);
		temp = temp->next;
	}
}

void display(){
	printf("\t\t\t\t\t\t\t\t");
	if(head == NULL)	printf("nothing to display");
	else{
		struct node* top = head;
		while(top != NULL){
			printf("%d ", top->data);
			top = top->next;
		}
	}
}

void add(){
	int n, d;
	printf("enter number of elements to be added in front : ");
	scanf("%d", &n);
	printf("enter elements : ");
	while(n--){
		scanf("%d", &d);
		struct node* temp = (struct node*) malloc(sizeof(struct node));
		temp->data = d;
		temp->next = head;
		head = temp;
	}
	display();
}

void append(){
	int n, d;
	printf("enter the number of elements to be appended : ");
	scanf("%d", &n);
	printf("enter elements to be appended : ");
	while(n--){
		scanf("%d", &d);
		if(head == NULL){
			head = (struct node*) malloc(sizeof(struct node));
			head->data = d;
			head->next = NULL;
		}
		else{
			struct node* temp = head;
			struct node* temp1 = (struct node*) malloc(sizeof(struct node));
			while(temp->next != NULL)	temp = temp->next;
			temp1->data = d;
			temp1->next = NULL;
			temp->next = temp1;
		}
	}
	display();
}

void insertat(){
	int a, n, check = 0;
	printf("enter element after which new element needs to be inserted : ");
	scanf("%d", &a);
	struct node* temp = head;
	while(temp != NULL){	
		if(temp->data == a){	
			check = 1;break;
		}
		temp = temp->next;
	}
	if(check){
		printf("enter element to be inserted:"); 
		scanf("%d", &n);
		struct node* temp1 = (struct node*) malloc(sizeof(struct node));
		temp1->data = n;
		struct node* temp2 = temp->next;
		temp->next = temp1;
		temp1->next = temp2;
		display();
	}
	else
		printf("element not in linked list");
}

void delfront(){
	if(head == NULL)
		printf("nothing to delete");
	else{
		head = head->next;
		display();
	}
}

void delback(){
	if(head == NULL)	printf("nothing to delete");
	else if(head->next == NULL)	{	head = NULL;	display();}
	else{
		struct node* temp = head;
		while((temp->next)->next != NULL)	temp = temp->next;
			temp->next = NULL;
		display();
	}
}

void delat(){
	if(head == NULL)	printf("nothing to delete");
	else{
		int a;
		printf("enter element to be deleted : ");
		scanf("%d", &a);
		struct node* temp = head;
		if(a == head->data)	delfront();
		else{	
			while((temp->next)->data != a)	temp = temp->next;
			temp->next = temp->next->next;
			display();
		}
	}
}

void swap(struct node* a, struct node* b){
  int temp = a->data;
	a->data = b->data;
	b->data = temp;
}


void bubsort(){
	struct node* t = head;
	int n = 0;
	while(t->next != NULL)	{ n++;	t = t->next;}
	t = head;
	int i = n, a = n;
	while(a--){
		while(i--){
			if(t->data > t->next->data)
				swap(t, t->next);
			t = t->next;
		}
		display();
		printf("\n");
		i = n;
		t = head;
	}
	printf("final linked list : \n");
	display();
}

void selsort(){
	int n = 0;
	struct node* temp = head;
	struct node* i = head;
	struct node* j;
	struct node* min;	
	while(i != NULL){
		min = i;
		j = i->next;
		while(j != NULL){
			if(j->data < min->data)
				min = j;
			j = j->next;
		}
		if(min->data < i->data)
			swap(min, i);
		i = i->next;
		display();
		printf("\n");
	}
	printf("final linked list : \n");
	display();
}

int main(){
	printf("1) Add elements in front\n2) Append elements at the end\n3) Insert elements in between\n4) Delete first element\n5) Delete last element\n6) Delete any element\n7) Bubble sort\n8) Selection sort\n9) Separate into even and odd elements\n10) Display linked list\n11) Polynomial operations\n12) Show menu\n0) Exit");
	int n, c = 1;

	while(c){
		printf("\n");
		scanf("%d", &n);
		switch(n){
			case 1:	{	printf("\r");	add(); break;}
			case 2: { append();	break;}
			case 3: { insertat();	break;}
			case 4: {	delfront(); break;}
			case 5: { delback(); break;}
			case 6: { delat(); break;}
			case 7: {	bubsort();	break;}
			case 8: {	selsort(); break;}
			case 9:	{	evenodd();	break;}
			case 10: {	display(); break;}
			case 11: { polyinitiate(); break;}
			case 12: {   printf("1) Add elements in front\n2) Append elements at the end\n3) Insert elements in between\n4) Delete first element\n5) Delete last element\n6) Delete any element\n7) Bubble sort\n8) Selection sort\n9) Separate into even and odd elements\n10) Display linked list\n11) Polynomial operations\n12) Show menu\n0) Exit");	printf("\n"); break;}
			case 0: c = 0;
		}
	}
}

