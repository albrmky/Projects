#ifndef PATIENTS_H_INCLUDED
#define PATIENTS_H_INCLUDED

#define ID_WIDTH 5
#define NAME_WIDTH	30
#define GENDER_WIDTH	7

typedef struct
{
	char name[NAME_WIDTH];
	int age;
	char gender[GENDER_WIDTH];
	char ID[ID_WIDTH];
} pat_data;

typedef struct patient
{
	pat_data patient;
	struct patient *next;
} P_Node;

void PatRec_Prepend(P_Node **Head, pat_data p_data);
void PatRec_print(P_Node *Head);
void PatRec_delete(P_Node **Head, char *id);
void PatRec_save(P_Node *Head);
void Patrec_load(P_Node **Head);
P_Node* PatRec_search(P_Node *Head, char *id);

#endif // PATIENTS_H_INCLUDED
