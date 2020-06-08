#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// Private NodeObj type
// Contains fields for data and pointers to the next and 
// previous Nodes of the cursor Node of the List.
typedef struct NodeObj {
    int data;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

// Private Node type
typedef NodeObj* Node;

// Private ListObj type
// Contains fields for front, back, and cursor Nodes of the List
// and the length of the List and the index of the cursor Node.
typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// Returns reference to new Node object
// Initializes data, next, and prev fields of the Node object
Node newNode(int data) {
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return(N);
}

// Frees all heap memory associated with its Node* argument, and sets *pN to NULL
void freeNode(Node* pN) {
    if( pN!=NULL && *pN!=NULL ) {
        free(*pN);
        *pN = NULL;
    }
}

// Returns reference to new empty List object
// Initializes the front, back, and cursor Nodes to NULL and the 
// length of the List to 0 and the index of the cursor Node to -1.
List newList(void) {
    List L;
    L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return(L);
}

// Frees all heap memory associated with its List* argument, and sets *pL to NULL
void freeList(List* pL) {
    if(pL!=NULL && *pL!=NULL) { 
        while( !isEmpty(*pL) ) { 
            deleteFront(*pL); 
        }
        free(*pL);
        *pL = NULL;
    }
}

// Access functions -----------------------------------------------------------

// Returns true (1) if this List is empty, otherwise returns false (0)
int isEmpty(List L){
    if( L==NULL ){
        printf("List Error: calling isEmpty() on NULL List reference\n");
        exit(1);
    }

    return(L->length==0);
}

// Returns the number of elements in this List
int length(List L) {

    // Check if the List is NULL
    if( L==NULL ) {
        printf("List Error: calling length() on NULL List reference\n");
        exit(1);
    }

    return(L->length);
}

// If cursor is defined, returns the index of the cursor element,
// otherwise returns -1.
int place(List L) {

    // Check if the List is NULL
    if( L==NULL ) {
        printf("List Error: calling place() on NULL List reference\n");
        exit(1);
    }

    return(L->index);
}

// Returns the front element of this List
int front(List L){

    // Check if the List is NULL
    if( L==NULL ){
        printf("List Error: calling front() on NULL List reference\n");
        exit(1);
    }
    // Check if the length of the List is less than 0
    if(L->length <= 0){
        printf("List Error: calling front() on an empty List\n");
        exit(1);
    }

    return(L->front->data);
}

// Returns the back element of this List
int back(List L){

    // Check if the List is NULL
    if( L==NULL ){
        printf("List Error: calling back() on NULL List reference\n");
        exit(1);
    }
    // Check if the length of the List is less than 0
    if(L->length <= 0){
        printf("List Error: calling back() on an empty List\n");
        exit(1);
    }

    return(L->back->data);
}

// Returns the cursor element of this List
int get(List L){

    // Check if the List is NULL
    if( L==NULL ){
        printf("List Error: calling get() on NULL List reference\n");
        exit(1);
    }
    // Check if the length of the List is less than 0
    // or if the cursor element is undefined
    if(L->length <= 0 || L->index<0){
        printf("List Error: calling get() on an empty List\n");
        exit(1);
    }

    return(L->cursor->data);
}

// Returns true (1) if the Lists are identical, false (0) otherwise
int equals(List A, List B){
    int eq = 0;
    Node N = NULL;
    Node M = NULL;

    // Check if either of the Lists inputted are NULL
    if( A==NULL || B==NULL ){
        printf("List Error: calling equals() on NULL List reference\n");
        exit(1);
    }

    // Check if the length of the Lists are equal
    eq = ( A->length == B->length );

    N = A->front;
    M = B->front;

    // Execute the loop if the elements of the Lists are equal and if the Lists
    // are not NULL
    while(eq && N!=NULL){
        eq = (N->data==M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

// Manipulation procedures ----------------------------------------------------

// Empties this List and sets it back to its default state
void clear(List L) {

    // Check if the List is NULL
    if(L == NULL) {
        printf("List Error: calling clear() on NULL List reference\n");
        exit(1);
    }
    
    // Keep deleting the front Node if the List is not empty
    while( !isEmpty(L) ) { 
        deleteFront(L); 
    }

    // Set the List back to its default state
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
}

// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L) {

    // Check if the List is NULL
    if(L == NULL) {
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(1);
    }

    // Checks if the List is empty
    if(L->length > 0) {
        L->cursor = L->front;
        L->index = 0;
    }
}

// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L) {

    // Check if the List is NULL
    if(L == NULL) {
        printf("List Error: calling moveBack() on NULL List reference\n");
        exit(1);
    }

    // Check if the List is empty
    if(L->length > 0) {
        L->cursor = L->back;
        L->index = L->length-1;
    }
}

void movePrev(List L) {

    // Check if the List is NULL
    if(L == NULL) {
        printf("List Error: calling movePrev() on NULL List reference\n");
        exit(1);
    }

    // If the cursor is defined and not at the front, move the
    // cursor to its previous Node
    if(L->cursor!=NULL && L->cursor!=L->front) {
        L->cursor = L->cursor->prev;
        L->index--;
    
    // If the cursor is defined and at the front, cursor becomes undefined
    } else if(L->cursor!=NULL && L->cursor==L->front) {
        L->cursor = NULL;
        L->index = -1;
    }
}

void moveNext(List L) {

    // Check if the List is NULL
    if(L == NULL) {
        printf("List Error: calling moveNext() on NULL List reference\n");
        exit(1);
    }

    // If the cursor is defined and not at the back, move the
    // cursor to its next Node
    if(L->cursor!=NULL && L->cursor!=L->back) {
        L->cursor = L->cursor->next;
        L->index++;

    // If the cursor is defined and at the back, cursor becomes undefined
    } else if(L->cursor!=NULL && L->cursor==L->back) {
        L->cursor = NULL;
        L->index = -1;
    }
}

void prepend(List L, int data) {

    // Check if the List is NULL
    if(L == NULL) {
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(1);
    }

    // Create new Node
    Node N = newNode(data);

    // If the List is empty, insert the new Node, so the new 
    // Node is now the front and back Node of the List
    if(L->length < 1) {
        L->front = L->back = N;
    // Else, insert the Node at the front of the List, so the new Node is now the front Node
    } else {
        L->front->prev = N;
        N->next = L->front;
        L->front = N;
        if(L->index != -1) {
            L->index++;
        }
    }
    L->length++;
}

void append(List L, int data) {

    // Check if the List is NULL
    if(L == NULL) {
        printf("List Error: calling append() on NULL List reference\n");
        exit(1);
    }

    // Create a new Node
    Node N = newNode(data);

    // If the List is empty, insert the new Node, so the new 
    // Node is now the front and back Node of the List
    if(L->length < 1) { 
        L->front = L->back = N;
    // Else, insert the Node at the back of the List, so the new Node is now the back Node
    } else { 
        L->back->next = N;
        N->prev = L->back;
        L->back = N;
    }
    L->length++;
}

void insertBefore(List L, int data) {

    // Check if the List is NULL
    if(L == NULL) {
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(1);
    }
    // Check if the List is empty or if the cursor is undefined
    if(L->length<=0 || L->index<0){
        printf("List Error: insertBefore() called on empty List");
        exit(1);
    }

    if(L->length > 0) {

        // If the cursor is the front Node, insert the new Node
        // into the front of the List, so the new Node now becomes the front Node
        if(L->index == 0) {
            Node N = newNode(data);
            L->cursor->prev = N;
            N->next = L->cursor;
            L->front = N;
            L->length++;
            L->index++;

        // If the cursor is not the front Node, insert the new Node
        // into the List before the cursor Node
        } else if(L->index > 0) {
            Node N = newNode(data);
            L->cursor->prev->next = N;
            N->prev = L->cursor->prev;
            L->cursor->prev = N;
            N->next = L->cursor;
            L->length++;
            L->index++;
        }

    }
}

void insertAfter(List L, int data) {

    // Check if the List is NULL
    if(L == NULL) {
        printf("List Error: calling insertAfter() on NULL List reference\n");
        exit(1);
    }
    // Check if the List is empty or if the cursor is undefined
    if(L->length<=0 || L->index<0){
        printf("List Error: insertAfter() called on empty List");
        exit(1);
    }

    if(L->length > 0) {

        // If the cursor is the back Node, insert the new Node
        // into the the back of the List, so the new Node now becomes the back Node
        if(L->index == L->length-1) {
            Node N = newNode(data);
            L->cursor->next = N;
            N->prev = L->cursor;
            L->back = N;
            L->length++;

        // If the cursor is not the back Node, insert the new Node
        // into the List after the cursor Node
        } else if(L->index >= 0) {
            Node N = newNode(data);
            L->cursor->next->prev = N;
            N->next = L->cursor->next;
            L->cursor->next = N;
            N->prev = L->cursor;
            L->length++;
        }

    }
}

void deleteFront(List L) {

    // Check if the List is NULL
    if(L == NULL) {
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(1);
    }
    // Check if the List is empty
    if(L->length<=0){
        printf("List Error: deleteFront() called on empty List");
        exit(1);
    }

    if(L->length > 0) {
        Node N = L->front;
        // Check if there is more than 1 Node in the List
        if(L->length > 1) {
            // If the cursor is the front Node, then delete it
            if(L->cursor == L->front) {
                L->cursor = NULL;
                L->index = -1;
            // If the cursor is not the front Node, the index of the cursor
            // will decrease by 1 because we are deleting the front Node
            } else if(L->cursor != NULL) {
                L->index--;
            }
            // Delete the front Node
            L->front = L->front->next;
            L->front->prev = NULL;
        // If there is only 1 Node in the List, then delete it
        } else {
            L->front = L->back = L->cursor = NULL;
            L->index = -1;
        }

        L->length--;
        freeNode(&N);

    }
}

void deleteBack(List L) {

    // Check if the List is NULL
    if(L == NULL) {
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(1);
    }
    // Check if the List is empty
    if(L->length<=0){
        printf("List Error: deleteBack() called on empty List");
        exit(1);
    }

    if(L->length > 0) {
        Node N = L->back;
        // Check if the List has more than 1 Node
        if(L->length > 1) {
            // If the cursor is the back Node, then delete it
            if(L->cursor == L->back) {
                L->cursor = NULL;
                L->index = -1;
            }
            // Delete the back Node
            L->back = L->back->prev;
            L->back->next = NULL;
        // If there is only 1 Node in the List, then delete it
        } else {
            L->front = L->back = L->cursor = NULL;
            L->index = -1;
        }

        L->length--;
        freeNode(&N);
    }
}

void delete(List L) {

    // Check if the List is NULL
    if(L == NULL) {
        printf("List Error: calling delete() on NULL List reference\n");
        exit(1);
    }
    // Check if the List is empty
    if(L->length<=0 || L->index<0){
        printf("List Error: delete() called on empty List");
        exit(1);
    }

    if(L->length > 0) {
        Node N = L->cursor;
        // If there is only 1 Node in the List, then delete it
        if(L->length == 1){
            L->front = L->back = L->cursor = NULL;
        // If the cursor is the front Node, then delete it
        } else if(L->index == 0) {
            L->cursor = NULL;
            L->front = L->front->next;
            L->front->prev = NULL;
        // If the cursor is the back Node, then delete it
        } else if(L->index == L->length-1) {
            L->cursor = NULL;
            L->back = L->back->prev;
            L->back->next = NULL;
        // If the cursor is not the front or back Node, then delete it
        } else {
            L->cursor->prev->next = L->cursor->next;
            L->cursor->next->prev = L->cursor->prev;
            L->cursor = NULL;
        }

        L->index = -1;
        L->length--;
        freeNode(&N);
    }
}

// Other operations -----------------------------------------------------------

void printList(FILE* out, List L){

   Node N = NULL;
    // Check if the List is NULL
    if( L==NULL ){
        printf("List Error: calling printList() on NULL List reference\n");
        exit(1);
    }

    // Print each element in the List to the file pointed to by out
    for(N = L->front; N != NULL; N = N->next){
        fprintf(out, "%d", N->data);
        if(N->next != NULL) {
            fprintf(out, " ");
        }
    }
}

// Returns a new List representing the same integer sequence as this 
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L) {

    // Check if the list is NULL
    if( L==NULL ){
      printf("List Error: calling copyList() on NULL List reference\n");
      exit(1);
    }
    List M = newList();
    Node N = L->front;

    while(N != NULL){
        append(M,N->data);
        N = N->next;
    }

    return M;
}