/*NAME: CAO XU
EMAIL: cxcharlie@gmail.com
ID: 704551688*/

#include <stdlib.h>
#include <sched.h>
#include <string.h>
#include "SortedList.h"

void SortedList_insert(SortedList_t *list, SortedListElement_t *element)
{
  if (list == NULL || element == NULL || list->key != NULL)//for the third one:
    //for this to work, you have to (as you should) give the HEAD of *list
    {
      return;
    }
  SortedListElement_t* cur = list->next;
  while(cur != list) //doubly linked
    {
      if(strcmp(element->key, cur->key) <= 0)
	{
	  break;
	}
      cur = cur->next;
    } //found correct place to insert
  if (opt_yield & INSERT_YIELD)
    sched_yield();
  element->next = cur;
  element->prev = cur->prev;
  cur->prev->next=element;
  cur->prev = element;
}


int SortedList_delete( SortedListElement_t *element)
{
  if (element == NULL || element->key == NULL || element->next->prev != element || element->prev->next != element)
    {
      return 1; //not sure what the first two errors should return
    }
  if (opt_yield & DELETE_YIELD)
    {
      sched_yield();
    }
  element->prev->next = element->next;
  element->next->prev = element ->prev;
  return 0;
}

SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key)
{
  if(key == NULL)
    return NULL;
  if (list==NULL)
    return NULL;
  if (list->key != NULL)
    return NULL;
  SortedListElement_t* cur = list->next;
  while(cur != list)
    {
      if(strcmp(cur->key, key) == 0)
	{
	  return cur;
	}
      if (opt_yield & LOOKUP_YIELD)
	sched_yield();
      cur = cur->next;
    }
  return NULL;
}

int SortedList_length(SortedList_t *list)
{
  int length = 0;
  if (list == NULL)
    return -1;
  if (list->key != NULL)//!!!
    return -1;
  SortedListElement_t* cur = list->next;
  while(cur!=list)
    {
      if(cur->next->prev != cur || cur->prev->next != cur)
	return -1; //corruption
      length++;
      if(opt_yield & LOOKUP_YIELD)
	sched_yield();
      cur = cur->next;
    }
  return length;
}
