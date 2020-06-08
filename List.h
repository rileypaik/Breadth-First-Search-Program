#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_
#include <stdio.h>
#include <stdlib.h>

// Exported type --------------------------------------------------------------
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// Returns reference to new empty List object
List newList(void);

// Frees all heap memory associated with its List* argument, and sets *pL to NULL
void freeList(List* pL);

// Access functions -----------------------------------------------------------

// Returns true (1) if this List is empty, otherwise returns false (0)
int isEmpty(List L);

// Returns the number of elements in this List
int length(List L);

// If cursor is defined, returns the index of the cursor element,
// otherwise returns -1.
int place(List L);

// Returns the front element of this List
int front(List L);

// Returns the back element of this List
int back(List L);

// Returns the cursor element of this List
int get(List L);

// Returns true (1) if the Lists are identical, false (0) otherwise
int equals(List A, List B);

// Manipulation procedures ----------------------------------------------------

// Empties this List and sets it back to its default state
void clear(List L);

// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L);

// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L);

// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L);

// If cursor is defined and not at back, moves cursor one step toward 
// back of this List, if cursor is defined and at back, cursor becomes 
// undefined, if cursor is undefined does nothing.
void moveNext(List L);

// Insert new Node into this List. If List is non-empty,
// insertion takes place before front Node.
void prepend(List L, int data);

// Insert new Node into this List. If List is non-empty,
// insertion takes place after back Node.
void append(List L, int data);

// Insert new Node into this List before the cursor
void insertBefore(List L, int data);

// Insert new Node into this List after the cursor
void insertAfter(List L, int data);

// Deletes the front Node of this List
void deleteFront(List L);

// Deletes the back Node of this List
void deleteBack(List L);

// Deletes the cursor Node, making the cursor undefined
void delete(List L);

// Other operations -----------------------------------------------------------

// Prints all elements in this List out to the output file on a single line
void printList(FILE* out, List L);

// Returns a new List representing the same integer sequence as this 
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L);

#endif