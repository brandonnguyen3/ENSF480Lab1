/*
File Name: dictionaryList.cpp
Assignment: Lab 1 Exercise B
Completed by: Brandon Nguyen, Darin Vicaldo
Completed on: Sept.11 2024
*/

#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include "dictionaryList.h"
#include "mystring_B.h"

using namespace std;

Node::Node(const Key& keyA, const Datum& datumA, Node *nextA)
  : keyM(keyA), datumM(datumA), nextM(nextA)
{
}

DictionaryList::DictionaryList()
  : sizeM(0), headM(0), cursorM(0)
{
}

DictionaryList::DictionaryList(const DictionaryList& source)
{
  copy(source);
}

DictionaryList& DictionaryList::operator =(const DictionaryList& rhs)
{
  if (this != &rhs) {
    destroy();
    copy(rhs);
  }
  return *this;
}

DictionaryList::~DictionaryList()
{
  destroy();
}

int DictionaryList::size() const
{
  return sizeM;
}

int DictionaryList::cursor_ok() const
{
  return cursorM != 0;
}

const Key& DictionaryList::cursor_key() const
{
  assert(cursor_ok());
  return cursorM->keyM;
}

const Datum& DictionaryList::cursor_datum() const
{
  assert(cursor_ok());
  return cursorM->datumM;
}

void DictionaryList::insert(const int& keyA, const Mystring& datumA)
{
  // Add new node at head?                                                                                  
  if (headM == 0 || keyA < headM->keyM) {
    headM = new Node(keyA, datumA, headM);
    sizeM++;
  }
	
  // Overwrite datum at head?                                                                               
  else if (keyA == headM->keyM)
    headM->datumM = datumA;
	
  // Have to search ...                                                                                     
  else {
      
    //POINT ONE
		
    // if key is found in list, just overwrite data;                                                        
    for (Node *p = headM; p !=0; p = p->nextM)
		{
			if(keyA == p->keyM)
			{
				p->datumM = datumA;
				return;
			}
		}
		
    //OK, find place to insert new node ...                                                                 
    Node *p = headM ->nextM;
    Node *prev = headM;
		
    while(p !=0 && keyA >p->keyM)
		{
			prev = p;
			p = p->nextM;
		}
		
    prev->nextM = new Node(keyA, datumA, p);
    sizeM++;
  }
  cursorM = NULL;
	
}

void DictionaryList::remove(const int& keyA)
{
    if (headM == 0 || keyA < headM -> keyM)
        return;
    
    Node *doomed_node = 0;
    
    if (keyA == headM-> keyM) {
        doomed_node = headM;
        headM = headM->nextM;
        
        // POINT TWO
    }
    else {
        Node *before = headM;
        Node *maybe_doomed = headM->nextM;
        while(maybe_doomed != 0 && keyA > maybe_doomed-> keyM) {
            before = maybe_doomed;
            maybe_doomed = maybe_doomed->nextM;
        }
        
        if (maybe_doomed != 0 && maybe_doomed->keyM == keyA) {
            doomed_node = maybe_doomed;
            before->nextM = maybe_doomed->nextM;
        }
        
        
    } 
    if(doomed_node == cursorM)
        cursorM = 0;
    
    delete doomed_node;           // Does nothing if doomed_node == 0.
    sizeM--;
}

void DictionaryList::go_to_first()
{
    cursorM = headM;
}

void DictionaryList::step_fwd()
{
    assert(cursor_ok());
    cursorM = cursorM->nextM;
}

void DictionaryList::make_empty()
{
    destroy();
    sizeM = 0;
    cursorM = 0;
}


// The following function are supposed to be completed by the stuents, as part
// of the exercise B part II. the given fucntion are in fact place-holders for
// find, destroy and copy, in order to allow successful linking when you're
// testing insert and remove. Replace them with the definitions that work.

void DictionaryList::find(const Key& keyA)
{
    Node *p = headM;
    while(p != 0){
      if (p->keyM == keyA){
        cursorM = p;
        return;
      }
      p = p->nextM;
    }
    cursorM = 0;
}


void DictionaryList::destroy()
{
  //checks the case in which there is nothing to destroy or it is empty
  if (headM == 0)
  {
    return;
  }

  Node *current = headM;
  
  while(current != 0){
    Node *next = current->nextM;
    delete current;
    current = next;
  }


  cursorM = 0;
  sizeM = 0;
  headM = 0;
}


void DictionaryList::copy(const DictionaryList& source)
{
    //Handles the edge case where the source list is empty
    if (source.headM == 0)
    {
        this->headM = 0;
        this->cursorM = 0;
        this->sizeM = 0;
        return;
    }

    //Initialization
    this->headM = 0;
    this->cursorM = 0;
    this->sizeM = 0;

    /*Creates two pointers. Current will start at the source's head. Next will be initialized with 0*/
    Node* sourcePointer = source.headM;
    Node* copyPointer = 0;

    //Code for creating the 1st node. Creates the first node and initializes it with the source's value at the head
    this->headM = new Node(sourcePointer->keyM, sourcePointer->datumM, 0);

    //moves the copy pointer up 
    copyPointer = this->headM;

    //increases the size. 
    this->sizeM++;

    //Using the same strategy as above, create the rest of the nodes. 
    while (sourcePointer->nextM != 0)
    {
        //moves the sourcePointer up to the next 
        sourcePointer = sourcePointer->nextM;

        //creates the next new node with the data from the source
        copyPointer->nextM = new Node(sourcePointer->keyM, sourcePointer->datumM, 0);

        //Update the copy's cursor if it equals the source's cursor position
        if (source.cursorM == sourcePointer)
        {
            this->cursorM = copyPointer->nextM;
        }
        copyPointer = copyPointer->nextM;
        this->sizeM++;
    }

    //sets cursorM if we run into the case that it was at the head.
    if (source.cursorM == source.headM)
    {
        this->cursorM = this->headM;
    }
}
