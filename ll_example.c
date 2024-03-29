// Fig. 12.3: fig12_03.c
// Inserting and deleting nodes in a list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// self-referential structure                       
struct Node {        
   char Name[30];                          
   int id; // each listNode contains a character 
   struct Node *nextPtr; // pointer to next node
   struct Node *prevPtr; // poitner to previous node
}; // end structure listNode                        

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr; // synonym for ListNode*

// prototypes

int deletes( LLPtr *sPtr, int studentid );
int isEmpty( LLPtr sPtr );
void insert( LLPtr *sPtr, int studentid, char name[30]);
void printList( LLPtr currentPtr );
void Reverseprint( LLPtr currentPt);
void instructions( void );
void freeall(LLPtr *sPtr);

int main( void )
{ 
   LLPtr startPtr = NULL; // initially there are no nodes
   unsigned int choice; // user's choice
   int item; // char entered by user
   char name[30];
   instructions(); // display the menu
   printf( "%s", "? " );
   scanf( "%u", &choice );

   // loop while user does not choose 3
   while (choice != 3) { 

      switch ( choice ) { 
         case 1:
            printf( "%s", "Enter a StudentID: " );
            scanf( "%d", &item );
            printf("%s","Enter Student Name: ");
            scanf("%s", name);
            insert( &startPtr, item ,name); // insert item in list
            printList( startPtr );
            Reverseprint(startPtr);
            break;
         case 2: // delete an element
            // if list is not empty
            if ( !isEmpty( startPtr ) ) { 
               printf( "%s", "Enter StudentID to be deleted: " );
               scanf( "%d", &item );

               // if character is found, remove it
               if ( deletes( &startPtr, item ) ) { // remove item
                  printf( "%d deleted.\n", item );
                  printList( startPtr );
                  Reverseprint(startPtr);
               } // end if
               else {
                  printf( "%d not found.\n\n", item );
               } // end else
            } // end if
            else {
               puts( "List is empty.\n" );
            } // end else

            break;
         default:
            puts( "Invalid choice.\n" );
            instructions();
            break;
      } // end switch

      printf( "%s", "? " );
      scanf( "%u", &choice );
   } // end while
  /* Clear all nodes at the end of nodes*/
   if(!isEmpty(startPtr)) freeall(&startPtr);
   puts( "End of run." );
} // end main

// display program instructions to user
void instructions( void )
{ 
   puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
} // end function instructions

// insert a new studentid into the list in sorted order
void insert( LLPtr *sPtr, int studentid ,char name[30])
{ 
   LLPtr newPtr; // pointer to new node
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list

   newPtr =(LLPtr) malloc( sizeof( LLnode ) ); // create node

   if ( newPtr != NULL ) { // is space available
      newPtr->id = studentid; // place studentid in node
      strcpy(newPtr->Name,name); //place name in node
      newPtr->nextPtr = NULL; // node does not link to another node
      newPtr->prevPtr = NULL; 
       
      previousPtr = NULL;
      currentPtr = *sPtr;

      // loop to find the correct location in the list       
      while ( currentPtr != NULL && studentid > currentPtr->id ) {
         previousPtr = currentPtr; // walk to ...               
         currentPtr = currentPtr->nextPtr; // ... next node 
      } // end while                                         

      // insert new node at beginning of list
      if ( previousPtr == NULL ) { 
         newPtr->nextPtr = *sPtr;
         if(currentPtr) currentPtr->prevPtr = newPtr;
         *sPtr = newPtr;
      
      } // end if
      else { // insert new node between previousPtr and currentPtr

         previousPtr->nextPtr = newPtr;
         newPtr->nextPtr = currentPtr;
 
         if(currentPtr) currentPtr->prevPtr = newPtr;
         newPtr->prevPtr = previousPtr;

      } // end else
   } // end if
   else {
      printf( "%d not inserted. No memory available.\n", studentid );
   } // end else
} // end function insert

// delete a list element
int deletes( LLPtr *sPtr, int studentid )
{ 
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list
   LLPtr tempPtr; // temporary node pointer

   // delete first node
   if ( studentid == ( *sPtr )->id ) { 
      tempPtr = *sPtr; // hold onto node being removed
      *sPtr = ( *sPtr )->nextPtr; // de-thread the node
      if(*sPtr) (*sPtr)->prevPtr = NULL;
      free( tempPtr ); // free the de-threaded node
      return studentid;
   } // end if
   else { 
      previousPtr = *sPtr;
      currentPtr = ( *sPtr )->nextPtr;

      // loop to find the correct location in the list
      while ( currentPtr != NULL && currentPtr->id != studentid ) { 
         previousPtr = currentPtr; // walk to ...  
         currentPtr = currentPtr->nextPtr; // ... next node  
      } // end while

      // delete node at currentPtr
      if ( currentPtr != NULL ) { 
         tempPtr = currentPtr;

         currentPtr = currentPtr->nextPtr;
         previousPtr->nextPtr = currentPtr;
         if(currentPtr) currentPtr->prevPtr = previousPtr;
         
         free( tempPtr );
         return studentid;
      } // end if
   } // end else

   return '\0';
} // end function delete

// return 1 if the list is empty, 0 otherwise
int isEmpty( LLPtr sPtr )
{ 
   return sPtr == NULL;
} // end function isEmpty

// print the list
void printList( LLPtr currentPtr )
{ 
   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } // end if
   else { 
      puts( "The list is:" );

      // while not the end of the list
      while ( currentPtr->nextPtr!= NULL ) {
         printf( "%d %s--> ", currentPtr->id, currentPtr->Name);

         currentPtr = currentPtr->nextPtr;   
      } // end while

      printf( "%d %s--> NULL\n",currentPtr->id, currentPtr->Name);
       

     
       
   } // end else
} // end function printList


void Reverseprint( LLPtr currentPtr )
{ 
   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } // end if
   else { 
      puts( "The list is:" );

      //move currentPtr to the end
      while ( currentPtr->nextPtr!= NULL ) {
         currentPtr = currentPtr->nextPtr;   
      } 

      //print node from the end
      while ( currentPtr->prevPtr!= NULL ) {
         printf( "%d %s--> ", currentPtr->id, currentPtr->Name);
         currentPtr = currentPtr->prevPtr;   
      } // end while

      printf( "%d %s--> NULL\n",currentPtr->id, currentPtr->Name);
       

     
       
   } // end else
} // end function printList

//free all node
void freeall(LLPtr *sPtr){
   LLPtr tmp;
   while(*(sPtr)!=NULL){
      tmp = (*sPtr);
      (*sPtr) = (*sPtr)->nextPtr;
      free(tmp);
   }
   printf("All node cleared\n");
}