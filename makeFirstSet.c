/*
 * Batch 13
 * Authors: Aditya Sarma, Abhinav Mehta.
 * 2013A7PS079P and 2013A7PS183P
 * f2013079@pilani.bits-pilani.ac.in & f2013183@pilani.bits-pilani.ac.in
 * Alex-1995 and Abhinav0208 - github handles.
 */// first set program
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "makeGrammar.h"
#include "makeFirstSet.h"

struct set* getSet(){
	struct set* newElement = (struct set*)malloc(sizeof(struct set));
	newElement->element = NULL;
	newElement->nextElement = NULL;
	return newElement;
}

struct firstSet* getFirstSet(){
	struct firstSet* newFirstSet = (struct firstSet*)malloc(sizeof(struct firstSet));
	newFirstSet->setOf = NULL;
	newFirstSet->elementList = NULL;
	newFirstSet->nextSet = NULL;
	return newFirstSet;
}

struct set* checkFirstSet(struct Grammar* grammar, char* name){
	struct Rule* tempRule = grammar->rules;
	struct set* newSet = getSet();
	struct set* parent = getSet();
	struct set* temp = getSet();
	struct set* previous = getSet();
	// if(newSet->element==NULL)printf("%s",newSet->element);
	while(tempRule!=NULL){
		if(strcmp(tempRule->start->name,name)==0){
			struct NodeList* tempNodeList = tempRule->rule_list;
			while(tempNodeList!=NULL){
			if(tempNodeList->node_list->is_token){
				temp = getSet();
				temp->element = tempNodeList->node_list->name;
				temp->nextElement = NULL;
				if(newSet->element==NULL) parent = temp;
				else newSet->nextElement = temp ;
				newSet = temp;
				}
			else if(newSet->element==NULL) 
				{
					temp = checkFirstSet(grammar,tempNodeList->node_list->name);
					parent=temp;
					while(temp->nextElement!=NULL){
					previous = temp;	
					temp = temp->nextElement;
					}
					if(strcmp(temp->element,"eps")==0){
					temp = previous;
					// printf("asd : %s",tempNodeList->node_list->next->name);
					if(!tempNodeList->node_list->next->is_token)temp->nextElement = checkFirstSet(grammar,tempNodeList->node_list->next->name);
					else {
						temp->nextElement = getSet();
						temp->nextElement->element=tempNodeList->node_list->next->name;
						temp=temp->nextElement;
						}
					}
					newSet=temp;
				}
			else {
				temp = checkFirstSet(grammar,tempNodeList->node_list->name);
				newSet->nextElement = temp;
				while(temp->nextElement!=NULL){
					previous = temp;
					temp = temp->nextElement;
				}
				if(strcmp(temp->element,"eps")==0){
					temp = previous;
					// printf("asd : %s",tempNodeList->node_list->name);
					temp->nextElement = checkFirstSet(grammar,tempNodeList->node_list->next->name);
				}
				newSet=temp;
			}
			// printf("%s ",newSet->element);
			tempNodeList = tempNodeList->nextList;
			}
			return parent;
		}
		tempRule = tempRule->nextRule;
	}
	return getSet();
}

struct firstSetList* makeFirstSetList(struct Grammar* grammar){
	struct Rule *tempRule = grammar->rules;
	struct firstSetList* firstSets = (struct firstSetList*)malloc(sizeof(struct firstSetList));
	firstSets->setList = NULL;
	struct firstSet* newFirstSet = getFirstSet();
	struct firstSet* tempSet = getFirstSet();
	while(tempRule!=NULL){
		tempSet = getFirstSet();
		tempSet->setOf = tempRule->start->name;
		// printf("%s --> ",tempSet->setOf);
		tempSet->elementList = checkFirstSet(grammar,tempRule->start->name);
		if(firstSets->setList==NULL){
			newFirstSet = tempSet;
			// printf(" %p\n",tempSet);
			firstSets->setList = newFirstSet;
		}
		else{
			newFirstSet->nextSet = tempSet;
			newFirstSet = tempSet ;
			// printf(" %p\n",tempSet);
		}
		// printf("\n");
		tempRule = tempRule->nextRule;
	}
	
	
	return firstSets;
}


void printSet(struct firstSetList* sets){
	struct firstSet* temp = sets->setList;
	while(temp!=NULL){
		printf("%s --> ",temp->setOf);
		struct set* tempSet = temp->elementList;
		while(tempSet!=NULL){
			printf("%s ",tempSet->element);
			tempSet = tempSet->nextElement;
		}
		printf("\n");
		temp = temp->nextSet;  
	}
}

// int main(int argc, char const *argv[])
// {
// 	char *filename = "grammar_list";
// 	struct Grammar* grammar = makeGrammar(filename);
// 	// printGrammar(grammar);
// 	struct firstSetList* sets = makeFirstSetList(grammar);
// 	printSet(sets);
// 	return 0;
// }


