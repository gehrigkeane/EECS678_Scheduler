/** @file libpriqueue.c
 */

#include <stdlib.h>
#include <stdio.h>

#include "libpriqueue.h"

/**
	Initializes the node_t data structure.
*/
node_t* node_init()
{
	node_t* newNode = (node_t*) malloc(sizeof(node_t));
	newNode->item = NULL;
	newNode->next = NULL;
	return newNode;
}

/**
	
*/
void* insert(node_t* n, void* item)
{
	void* oldItem = n->item;
	n->item = item;
	return oldItem;
}

/**
	Inserts a node directly after another node in the queue.

	@param n1 the node in the queue
	@parram n2 the node to insert
*/
void* insert_at(node_t* n1, node_t* n2)
{
	node_t* loc = n1->next;
	n1->next = n2;
	return (void*) loc;
}

/**
	
*/
void* get_item(node_t* n)
{
	return n->item;
}

/**
	Destroys and frees all memory associated with n.

	@param n a pointer to an instance of the node_t data structure
	@return the item from n
*/
void* node_destroy(node_t* n)
{
	void* itemFromDeletedNode = n->item;
	free(n);
	n = NULL;
	return itemFromDeletedNode;
}


/**
	Initializes the priqueue_t data structure.
	
	Assumtions
		- You may assume this function will only be called once per instance of priqueue_t
		- You may assume this function will be the first function called using an instance of priqueue_t.
	@param q a pointer to an instance of the priqueue_t data structure
	@param comparer a function pointer that compares two elements.
	See also @ref comparer-page
 */
void priqueue_init(priqueue_t *q, int(*comparer)(const void *, const void *))
{
	q->head = NULL;
	q->queueSize = 0;
	q->comp = comparer;
}


/**
	Inserts the specified element into this priority queue.

	@param q a pointer to an instance of the priqueue_t data structure
	@param ptr a pointer to the data to be inserted into the priority queue
	@return The zero-based index where ptr is stored in the priority queue, where 0 indicates that ptr was stored at the front of the priority queue.
 */
int priqueue_offer(priqueue_t *q, void *ptr)
{
	node_t* n = node_init();
	insert(n, ptr);

	if (q->head == NULL 
		|| q->comp(n->item, q->head->item) < 0)
	{
		// Store at the front of the queue
		insert_at(n, q->head);
		q->head = n;
		q->queueSize++;
		return 0;
	}
	else
	{
		// Go through the queue and find the place to insert
		node_t* currentNode = q->head;
		int i = 0;
		while (i < priqueue_size(q))
		{
			if (currentNode->next == NULL 
				|| q->comp(n->item, currentNode->next->item) < 0)
			{
				insert_at(n, currentNode->next);
				currentNode->next = n;
				q->queueSize++;
				return i;
			}
			
			currentNode = currentNode->next;
			i++;
		}
	}

	printf("Error inserting node");
	exit(1);
	return -1; // error
}


/**
	Retrieves, but does not remove, the head of this queue, returning NULL if
	this queue is empty.
 
	@param q a pointer to an instance of the priqueue_t data structure
	@return pointer to element at the head of the queue
	@return NULL if the queue is empty
 */
void *priqueue_peek(priqueue_t *q)
{
	return (priqueue_size(q) == 0) ? NULL : q->head->item;
}


/**
	Retrieves and removes the head of this queue, or NULL if this queue
	is empty.
 
	@param q a pointer to an instance of the priqueue_t data structure
	@return the head of this queue
	@return NULL if this queue is empty
 */
void *priqueue_poll(priqueue_t *q)
{
	if (q->queueSize == 0)
	{
		return NULL;
	}
	else
	{
		node_t* n = q->head;
		q->head = n->next;
		q->queueSize--;
		return node_destroy(n);
	}
}


/**
	Returns the element at the specified position in this list, or NULL if
	the queue does not contain an index'th element.
 
	@param q a pointer to an instance of the priqueue_t data structure
	@param index position of retrieved element
	@return the index'th element in the queue
	@return NULL if the queue does not contain the index'th element
 */
void *priqueue_at(priqueue_t *q, int index)
{
	// TODO
	q;
	index;
	return NULL;
}


/**
	Removes all instances of ptr from the queue. 
	
	This function should not use the comparer function, but check if the data contained in each element of the queue is equal (==) to ptr.
 
	@param q a pointer to an instance of the priqueue_t data structure
	@param ptr address of element to be removed
	@return the number of entries removed
 */
int priqueue_remove(priqueue_t *q, void *ptr)
{
	// TODO
	q;
	ptr;
	return 0;
}


/**
	Removes the specified index from the queue, moving later elements up
	a spot in the queue to fill the gap.
 
	@param q a pointer to an instance of the priqueue_t data structure
	@param index position of element to be removed
	@return the element removed from the queue
	@return NULL if the specified index does not exist
 */
void *priqueue_remove_at(priqueue_t *q, int index)
{
	// TODO
	q;
	index;
	return 0;
}


/**
	Returns the number of elements in the queue.
 
	@param q a pointer to an instance of the priqueue_t data structure
	@return the number of elements in the queue
 */
int priqueue_size(priqueue_t *q)
{
	return q->queueSize;
}


/**
	Destroys and frees all the memory associated with q.
	
	@param q a pointer to an instance of the priqueue_t data structure
 */
void priqueue_destroy(priqueue_t *q)
{
	while (priqueue_size(q) > 0)
	{
		// Keep removing the head of the queue until empty
		priqueue_poll(q);
	}
}
