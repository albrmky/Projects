#include "Patients.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int record_size = 0;

void PatRec_Prepend(P_Node **Head, pat_data p_data)
{
	P_Node *temp = *Head; // local copy of the head pointer

	// P_Node creation and initialization
	P_Node *newNode = (P_Node*) malloc(sizeof(P_Node));
	newNode->patient = p_data;

	newNode->next = temp; // the new P_Node point to the same P_Node as the head
	(*Head) = newNode; // the head pointer is used to redirect the head to the newly created P_Node

	record_size++;
}

void PatRec_print(P_Node *Head)
{
	P_Node *ptr = Head; // a pointer for traversal

	printf("Head_> \n");

	while (ptr != NULL)
	{
		printf("*********************************************\n");
		printf("name: %s\n", (ptr->patient).name);
		printf("age: %d\n", ptr->patient.age);
		printf("gender: %s\n", ptr->patient.gender);
		printf("ID: %s\n", ptr->patient.ID);
		printf("**********************************************\n");
		ptr = ptr->next;
	}
	printf("</>\n");

}

void PatRec_delete(P_Node **Head, char *id)
{
	P_Node *ptr = *Head; // local copy of the head pointer
	P_Node *temp; // pointer to the node to be freed
	P_Node *prev_node = NULL; // pointer to the previous node to the one to be deleted

	if ( ptr == NULL ) return; // in case the list is empty

	while (strcmp(ptr->patient.ID, id)) // find the node to be deleted stop if found the node or the list end is reached
	{
		if ( ptr->next == NULL ) return;
		prev_node = ptr;
		ptr = ptr->next;
	}

	if ( ptr == *Head ) // in case the node to be deleted is the head
	{
		if ( ptr->next == NULL ) // in case there is only one element
		{
			*Head = NULL;
			free(ptr);
			return;
		}
		else
		{
			temp = *Head;
			*Head = (*Head)->next;
			free(temp);
			return;
		}

	}

	else // case the element to be deleted is not the head
	{
		temp = ptr; // reserve the address of the node to be deleted
		prev_node->next = ptr->next; // assign the next pointer of the previous node to the next of the current node
		free(temp);
	}
	record_size--;
}

void PatRec_save(P_Node *Head)
{
	P_Node *ptr = Head;
	FILE *filevar;
	filevar = fopen("Patient.dat", "w");

	if ( filevar )
	{
		fwrite(&record_size, sizeof(int), 1, filevar);

		while (ptr != NULL)
		{
			//printf("name: %s\n",(ptr->patient).name );
			fwrite(& (ptr->patient), sizeof(pat_data), 1, filevar);
			ptr = ptr->next;
		}

		fclose(filevar);
	}
	else
	{
		printf("failed");
	}

}

void Patrec_load(P_Node **Head)
{
	int size;
	pat_data data;
	FILE *filevar = fopen("Patient.dat", "r");
	if ( filevar )
	{
		fread(&size, sizeof(int), 1, filevar);

		//printf("size = %d\n",size);

		for (int i = 0; i < size; i++)
		{
			fread(&data, sizeof(pat_data), 1, filevar);
			PatRec_Prepend(Head, data);
		}

		fclose(filevar);

	}
	else
	{
		printf("patients data is missed :( \n");
	}

}

P_Node* PatRec_search(P_Node *Head, char *id)
{
	P_Node *ptr = Head; // a pointer for traversal

	if ( ptr == NULL ) return ptr;

	while (strcmp(ptr->patient.ID, id))
	{

		ptr = ptr->next;
		if ( ptr == NULL ) return ptr;
	}
	return ptr;

}

