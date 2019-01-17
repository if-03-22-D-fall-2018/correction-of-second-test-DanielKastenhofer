/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: <your class>
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			dictionary.cpp
 * Author:			P. Bauer
 * Due Date:		November 25, 2012
 * ----------------------------------------------------------
 * Description:
 * Implementation of dictionary.h.
 * ----------------------------------------------------------
 */
 #include "dictionary.h"
 #include "general.h"
 #include <stdlib.h>
 #include <stdbool.h>
 #include <strings.h>
 #include <string.h>

 typedef struct NodeImplementation* Node;

 struct NodeImplementation{
   const char* word;
   Node next;
 };

 struct DictionaryImplementation{
   int size;
   Node iterator;
   Node head;
 };

 Dictionary 	new_dictionary ()
 {
   Dictionary dictionary = (Dictionary)malloc(sizeof(struct DictionaryImplementation));
   dictionary->size = 0;
   dictionary->head = 0;
   dictionary->iterator = 0;
   return dictionary;
 }
 void 	delete_dictionary (Dictionary dictionary)
 {
   Node current = dictionary->head;

   while (current != 0) {
     sfree(current);
     current = current->next;
   }
   sfree(dictionary);
 }

 void 	add (Dictionary dict, const char *word)
 {
     Node current = dict->head;
     Node toAdd = (Node)malloc(sizeof(struct NodeImplementation));
     toAdd->word = word;
     toAdd->next = 0;

     if (dict->head == 0) {
       dict->head = toAdd;
       dict->size++;
     }
     else{
       while (current->next != 0 && current->word != word) {
         current = current->next;
       }
       if (current->word == word) return;
       current->next = toAdd;
       dict->size++;
     }
 }

 int 	get_size (Dictionary dict)
 {
   return dict->size;
 }

 bool 	is_in_dict (Dictionary dict, const char *word)
 {
   Node current = dict->head;

   while (current != 0) {
     if (strcasecmp(current->word, word) == 0) {
       return true;
     }
     current = current->next;
   }
   return false;
 }

 void start_iterating (Dictionary dict)
 {
   dict->iterator = dict->head;
 }

 bool has_next (Dictionary dict)
 {
   if (dict->iterator != 0) {
     return true;
   }
   return false;
 }

 const char * get_next_entry (Dictionary dict)
 {
   if (dict->iterator != 0 && has_next(dict)) {
       Node current = dict->iterator;
       dict->iterator = current->next;
       return current->word;
   }
   return 0;
 }

 void insert_sorted (Dictionary dict, const char *word)   //Reworked Method
 {
   if (is_in_dict(dict, word)) return;

     Node current = dict->head;
     Node toAdd = (Node)malloc(sizeof(struct NodeImplementation));
     toAdd->word = word;
     toAdd->next = 0;

     if (dict->head == 0) {
       dict->head = toAdd;
     }
     else if (dict->head->next == 0) {
       if (strcasecmp(dict->head->word, word) > 0) {
         toAdd->next = dict->head;
         dict->head = toAdd;
       }
       else
       {
         dict->head->next = toAdd;
       }
     }

     else if (strcasecmp(dict->head->word, word) > 0) {
       toAdd->next = dict->head;
       dict->head = toAdd;
     }
     else
     {
       while (current != 0 && current->next != 0 && 0 > strcasecmp(current->next->word, word)) {
         current = current->next;
       }

       if (current->next == 0) {
         dict->size--;
         add(dict, word);
       }
       if (strcasecmp(current->next->word, word) > 0) {
         toAdd->next = current->next;
         current->next = toAdd;
       }

     }
     dict->size++;
 }
