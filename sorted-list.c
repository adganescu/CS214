#include "sorted-list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int compareInts(void *p1, void *p2)
{
	int i1 = *(int*)p1;
	int i2 = *(int*)p2;

	return i1 - i2;
}

int compareDoubles(void *p1, void *p2)
{
	double d1 = *(double*)p1;
	double d2 = *(double*)p2;

	return (d1 < d2) ? -1 : ((d1 > d2) ? 1 : 0);
}

int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}

/*******************************************************/


node* createNode(void* data) {

	node *node = malloc(sizeof(node));
	node->refCount = 0;
	node->prev = NULL;
	node->next = NULL;
	node->data = data; 

	return node;
}

void printNode(node* node) {

	printf("%p\n", node->data);
	printf("%d", node->refCount);
	printf("\n");
}

void freeNode(node *node) {
	
}

void setCount(node* node, int i) {

	if (i == -1) {
		
		node->refCount = node->refCount - 1;

	} else if (i == 1) {
		node->refCount = node->refCount + 1;
	} else {} 

}

SortedListPtr SLCreate(CompareFuncT cf) {

	SortedListPtr list = malloc(sizeof(SortedListPtr));
	list->hasBegun = 0;
	list->head = NULL;
	list->funct = cf;
	list->len = 0;

	return list;
}

int SLInsert(SortedListPtr list, void *newObj) {


	void* obj = newObj;
	node* newNode = createNode(obj);
	node* pass = malloc(sizeof(node));
/*	printf("INSERT %s\n", (char*) newNode->data); */




	if (list->head == NULL) {
		list->head = createNode(obj);
		list->len = 1;	

		return 1;	
	}

	else if (list->len == 1) {

		
		if(list->funct(newNode->data, list->head->data) >= 0) {
			
			newNode->next = list->head;

			list->head = newNode;
			list->head->next->prev = list->head;
			list->head->next->refCount += 1;	
			list->len += 1;
		
			return 1;
		} else {
			
			list->head->next = newNode;
			newNode->prev = list->head;
			newNode->refCount += 1;
			list->len += 1;
			return 1;
				
		}

	} else if(list->len >= 2)  {

		pass = list->head;
		/*IF the LIST IS AT LEAST TWO ELEMENTS LONG*/
		/*HANDLING HEAD CASE*/
		if(list->funct(newNode->data, list->head->data) >= 0) {

			newNode->next = list->head;

			list->head = newNode;
			list->head->next->prev = list->head;
			list->head->next->refCount += 1;
			list->len += 1;
			

			return 1;
		}


		
		while(pass != NULL) {


		/*HANDLING TAIL CASE*/
			if(pass->next == NULL) {
			
				pass->next = newNode;
				setCount(newNode, 1);
				newNode->prev = pass;
				list->len += 1;
				return 1;

			}

		/*HANDLING MIDDLE CASE*/
			if(list->funct(newNode->data, pass->data) >=0) {

			
			newNode->prev = pass->prev;
			newNode->prev->next = newNode;
			pass->prev = newNode;
			newNode->next = pass;
			newNode->refCount += 1;
			list->len += 1;
			return 1;
			}
	
			pass = pass->next;
		}
	}
			
	return 0;
}



int SLRemove(SortedListPtr list, void* newObj) {


	node* pass;
	
	
	
	if(list->len == 1) {

		
		if (list->funct(list->head->data, newObj) == 0) {

			/*IF THERE IS ONLY ONE ELEMENT LEFT IN SORTED LIST*/
			list->head = NULL;
			list->len = 0;	
			return 1;
		} else { return 0; }

	}


	if(list->len == 0) {
	/* LEFT ALONE SO USER CAN STILL ADD VALUES IN LATER*/
		return 0;
	}

	pass = list->head;



	if(list->funct(pass->data, newObj) == 0) {
		/*DELETING HEAD*/

		
		
		setCount(pass, -1);		
		list->head = pass->next;
		/*list->head->prev = NULL*/;		
		setCount(list->head, -1);
	
		if (pass->refCount <= 0) {
		
		/* IF REF COUNT HITS ZERO ON HEAD, FREE*/
		
		 
	
		}	
		list->len -= 1;
		return 1;
	} else {
		/*STARTING TO RUN THROUGH*/

		pass = pass->next;
		while(pass != NULL) {

			if(list->funct(pass->data, newObj) == 0) {
			
				if(pass->next == NULL) {
					
				/*DELETING END OF LIST*/
			 	pass->refCount -= 1;
				pass->prev->next = NULL;

				if(pass->refCount <= 0) {
				/*FREE GARBAGE*/
					freeNode(pass);
				}
				list->len -= 1;
				return 1;
				} else {

				/*DELETING IN THE MIDDLE OF THE LIST*/

				pass->refCount -= 1;
						

				if (pass->refCount > 0)  {

				/* INCREMENT COUNT TO NEXT WHEN CURR HAS ITERATOR STILL*/				

					pass->next->refCount += 1;
				}
					pass->next->prev = pass->prev;
					pass->prev->next = pass->next;
					pass->prev = NULL;		
					
			
					if (pass->refCount <= 0) {
					/*FREE GARBAGE*/
			
					}

				list->len -= 1;
				return 1;
				}
								
			}

		pass = pass->next;
		}



	}

return 0;
}

void SLDestroy(SortedListPtr list) {

}

SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {

	struct SortedListIterator *iter = malloc(sizeof(SortedListIteratorPtr));
	iter->hasBegun = 0;
	iter->hasEnded = 0;
	iter->curr = list->head;
	iter->list = list;

return iter;
}

void* SLNextItem(SortedListIteratorPtr iter) {

	node *ret;
	if(iter == NULL) {
		printf("TELL ME NOW\n");

	}	
	
	if (iter->curr == NULL) {
		iter->curr = iter->list->head;

	}

	if (iter->hasBegun == 0) {
		
		/*IF CHECKING THE FIRST NODE OF A LIST*/
		if(iter->list->head != NULL) {
			iter->list->head->refCount += 1;
			iter->hasBegun += 1;
	
			return iter->list->head->data;
		} 
	} else {

		if(iter->curr->next == NULL) {

			/*LIST IS TEMPORARILY OVER, STUFF COULD STILL BE ADDED LATER*/
			return NULL;
		}

		if(iter->curr == iter->list->head || iter->curr->prev != NULL) { 

			iter->curr->refCount -= 1;
			iter->curr = iter->curr->next;
			iter->curr->refCount += 1;

			return iter->curr->data;
			
			/*THIS NODE HASN'T BEEN DELETED*/

			}
		else if (iter->curr->prev == NULL) {

			/*CURRENTLY ON A DELETED NODE*/

		}

		

		/*CHECKING ANY OTHER NODE IN THE LIST*/

	}

return NULL;
}

void stringTestCase1() {

void* val = "TEST";
int (*fun) (void*, void*) = compareStrings;

void* test = "f";
void* val2 = "e";
void* val3 = "d";
void* val4 = "c"; 
void* val5 = "d";
void* val6 = "a";

SortedListPtr list = SLCreate(fun);
SortedListIteratorPtr iter = SLCreateIterator(list);
SortedListIteratorPtr iter2 = SLCreateIterator(list);
node* node1 = createNode(val);
node* pass  = malloc(sizeof(node));

printf("STRING TEST CASE 1\n");

SLInsert(list, test);
SLInsert(list, val2);
SLInsert(list, val3);
SLInsert(list, val4);
SLInsert(list, val5);
SLInsert(list, val6);
/*
SLRemove(list, test);
SLRemove(list, val4);
SLRemove(list, val5);
SLRemove(list, val6);
SLRemove(list, val2);
SLRemove(list, val5);
SLRemove(list, val4);

SLInsert(list, val5);
*/

val = SLNextItem(iter);

printf("ITERATED VALUE IS %s\n\n", (char*) val);

val = SLNextItem(iter);

printf("ITERATED VALUE IS %s\n\n", (char*) val);

val = SLNextItem(iter);

printf("ITERATED VALUE IS %s\n\n", (char*) val);

val = SLNextItem(iter);

printf("ITERATED VALUE IS %s\n\n", (char*) val);

SLRemove(list, val4);

val = SLNextItem(iter);

printf("ITERATED VALUE IS %s\n\n", (char*) val);

val = SLNextItem(iter);

printf("ITERATED VALUE IS %s\n\n", (char*) val);

SLInsert(list, val6);

val = SLNextItem(iter);

printf("ITERATED VALUE IS %s\n\n", (char*) val);



pass = list->head;

while(pass != NULL) {
	
	printf("value is %s\n", (char*) pass->data);
	printf("COUNT: %d\n", pass->refCount);

	pass = pass->next;

}
printf("FINAL LEN %d\n", list->len);

setCount(node1, 1);

}




void doubleTestCase1() {

void* val = malloc(sizeof(double));
int (*fun) (void*, void*) = compareDoubles;


void* test = malloc(sizeof(double));
void* val2 = malloc(sizeof(double));
void* val3 = malloc(sizeof(double));
void* val4 = malloc(sizeof(double));
void* val5 = malloc(sizeof(double));
void* val6 = malloc(sizeof(double)); 
void* val7 = malloc(sizeof(double));


SortedListPtr list = SLCreate(fun);

node* node1 = createNode(val);
node* pass  = malloc(sizeof(node));

printf("DOUBLE TEST CASE 1\n");


*((double*)val) = 10;

*((double*)test) = 1.2;
*((double*)val2) = 1.2;
*((double*)val3) = 1.3;
*((double*)val4) = 1.4;
*((double*)val5) = 1.5;
*((double*)val6) = 1.6;
*((double*)val7) = 1.7;

SLInsert(list, test);
SLInsert(list, val2);
SLInsert(list, val3);
SLInsert(list, val4);
SLInsert(list, val5);
SLInsert(list, val6);
SLInsert(list, val7);

SLRemove(list, val4);


pass = list->head;

while(pass != NULL) {
	
	printf("value is %f\n", *((double*)pass->data));
	printf("COUNT: %d\n", pass->refCount);

	pass = pass->next;

}


setCount(node1, 1);
printf("FINAL LEN %d\n", list->len);



}


void intTestCase1() {

void* val = malloc(sizeof(int));
int (*fun) (void*, void*) = compareInts;

void* test = malloc(sizeof(int));
void* val2 = malloc(sizeof(int));
void* val3 = malloc(sizeof(int));
void* val4 = malloc(sizeof(int));
void* val5 = malloc(sizeof(int));
void* val6 = malloc(sizeof(int)); 

SortedListPtr list = SLCreate(fun);
SortedListIteratorPtr iter = SLCreateIterator(list);
node* node1 = createNode(val);
node* pass  = malloc(sizeof(node));

printf("INT TEST CASE 1\n");


*((int*)val) = 10;

*((int*)test) = 2;
*((int*)val2) = -1;
*((int*)val3) = -4;
*((int*)val4) = -5;
*((int*)val5) = -6;
*((int*)val6) = -7;


SLInsert(list, test);
SLInsert(list, val2);
SLInsert(list, val3);
SLInsert(list, val4);
SLInsert(list, val5);
SLInsert(list, val6);

SLRemove(list, val6);



pass = list->head;

while(pass != NULL) {
	
	printf("value is %d\n", *((int*)pass->data));
	printf("COUNT: %d\n", pass->refCount);

	pass = pass->next;

}


setCount(node1, 1);
printf("FINAL LEN %d\n", list->len);
SLDestroy(list);


}



int main() {

	printf("\n");

	doubleTestCase1();

	printf("\n");

	intTestCase1();

	printf("\n");

	stringTestCase1();


return 0;
}
