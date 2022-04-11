/*
 * program.c
 *
 *  Created on: Jan 20, 2022
 *      Author: noureldeen albrmky
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#include "Patients.h"
#include "program.h"

char *password = { "1234" };

reservation_slot slots_info[5];

extern P_Node *Patients_record;

void load_slots(void)
{
	FILE *filevar = fopen("Slots.dat", "r");
	if ( filevar )
	{
		fread(slots_info, sizeof(reservation_slot), 5, filevar);
		fclose(filevar);
	}

	else
	{
		printf("time_slots data is missed :(\n");
		init_slots();
	}

}

void save_slots(void)
{
	FILE *filevar = fopen("Slots.dat", "w");
	if ( filevar )
	{
		fwrite(slots_info, sizeof(reservation_slot), 5, filevar);
	}

	fclose(filevar);
}

void init_slots(void)
{
	reservation_slot temp1 = { "2->2:30", "    ", 0, 1 };
	reservation_slot temp2 = { "2:30->3", "    ", 0, 2 };
	reservation_slot temp3 = { "3->3:30", "    ", 0, 3 };
	reservation_slot temp4 = { "4->4:30", "    ", 0, 4 };
	reservation_slot temp5 = { "4:30->5", "    ", 0, 5 };

	slots_info[0] = temp1;
	slots_info[1] = temp2;
	slots_info[2] = temp3;
	slots_info[3] = temp4;
	slots_info[4] = temp5;

}

void print_slots(void)
{
	for (int i = 0; i < 5; i++)
	{
		printf("*********************************************************\n");
		printf("the slot number is: %d\n", slots_info[i].slot_number);
		printf("the slot name is: %s\n", slots_info[i].slot_name);
		printf("the slot id_info is: %s\n", slots_info[i].id_info);
		printf("the slot state is: %d\n", slots_info[i].state);
		printf("*********************************************************\n");
	}
}

void entry(void)
{
	printf(
			"**************************************************[Esc]->return \n");
	printf(
			"                                                  [Ctrl+c]->Exit\n");
	printf("Welcome to the system please choose the mode");
	printf("\n A: admin");
	printf("\n U: user\n");
	printf("**************************************************\n");
}

void admin_entry(void)
{
	printf(
			"**************************************************[Esc]->return \n");
	printf(
			"                                                  [Ctrl+c]->Exit\n");
	printf("            ADMIN MODE verification");
	printf("\n**************************************************\n");
}

int get_password(void)
{
	char pw[10] = { 0 };
	for (int j = 0; j < 3; j++)
	{
		printf("Enter your password: ");
		int i;

		for (i = 0; i < 10; i++)
		{
			pw[i] = getch();

			if ( pw[i] == 27 )
				return 27;
			else if ( pw[i] == 3 )
				return 3;
			else if ( pw[i] == 13 )
			{
				break;
			}
			printf("*");
		}

		pw[i] = '\0';
		printf("\n");

		if ( !strcmp(pw, password) )
		{
			return 1; // right password
		}
		else
		{
			printf("wrong password\n");
		}
	}
	return 0;
}

void display_reservations(void)
{
	printf(
			"****************************************************[Esc]->return\n");
	printf(
			"                                                    [Ctrl+c]->exit\n");
	printf("number\t time\t state\t id\n");
	for (int i = 0; i < 5; i++)
	{
		printf("%d\t %s", slots_info[i].slot_number, slots_info[i].slot_name);
		if ( slots_info[i].state )
			printf("\t reserved");
		else
			printf("\t available");

		printf("\t%s\n", slots_info[i].id_info);
	}
	printf("****************************************************\n\n");

}

void display_adminOptions(void)
{
	printf(
			"****************************************************[Esc]->return\n");
	printf(
			"                                                    [Ctrl+c]->exit\n");
	printf("Welcome Admin\n");
	printf("****************************************************\n\n");
	printf("Enter the number of the required option: \n");
	printf("1- Add a new patient record\n");
	printf("2- edit a patient record\n");
	printf("3- reserve an appointment\n");
	printf("4- Cancel an appointment\n");
	printf("5- print record\n");
	printf("****************************************************\n\n");

}

void display_userOptions(void)
{
	printf(
			"****************************************************[Esc]->return\n");
	printf(
			"                                                    [Ctrl+c]->exit\n");
	printf("Welcome User\n");
	printf("****************************************************\n\n");
	printf("Enter the number of the required option: \n");
	printf("1- View patient record\n");
	printf("2- View reservation table\n");
	printf("****************************************************\n\n");

}

void display_add_patient_entry(void)
{
	printf(
			"****************************************************[Esc]->return\n");
	printf(
			"                                                    [Ctrl+c]->exit\n");
	printf("adding a patient record\n");
	printf("****************************************************\n\n");
}

void display_edit_patient_entry(void)
{
	printf(
			"****************************************************[Esc]->return\n");
	printf(
			"                                                    [Ctrl+c]->exit\n");
	printf("editing a patient record\n");
	printf("****************************************************\n\n");
}

int check_id(char id[]) // 1 mean valid
{
	int flag = 1;

	if ( strlen(id) != ID_WIDTH - 1 )
	{
		flag = 0;
	}
	for (int i = 0; i < ID_WIDTH - 1; i++)
	{
		if ( !isdigit(id[i]) )
		{
			flag = 0;
			break;
		}
	}

	return flag;
}

int get_id(char arr[])
{
	char ch = 'k';
	char temp_id[ID_WIDTH];
	while (1)
	{
		if ( ch == 27 )
			return 27;
		else if ( ch == 3 ) return 3;

		system("cls");
		display_add_patient_entry();
		printf("Enter the patient ID: ");
		int i;
		for (i = 0; i < ID_WIDTH + 1; i++)
		{
			temp_id[i] = getch();

			if ( temp_id[i] == 27 )
				return 27;
			else if ( temp_id[i] == 3 )
				return 3;
			else if ( temp_id[i] == 13 ) break;

			printf("%c", temp_id[i]);
		}
		temp_id[i] = '\0';

		if ( PatRec_search(Patients_record, temp_id) )
		{
			printf("\nthis id is already registered\n");
			printf("press any key to re-try\n");
		}
		else
		{
			if ( check_id(temp_id) )
			{
				strcpy(arr, temp_id);
				return 0;
			}
			printf("\nthis is invalid id\n");
			printf("press any key to re-try");
		}

		ch = getch();
	} // while(1)

}

int get_name(char name[])
{
	char ch;
	char temp_name[NAME_WIDTH];
	char flag = 0;

	while (1)
	{

		if ( ch == 27 )
			return 27;
		else if ( ch == 3 ) return 3;

		system("cls");
		display_add_patient_entry();
		printf("Enter the patient name: ");
		flag = 0;

		int i;
		for (i = 0; i < NAME_WIDTH - 1; i++)
		{
			temp_name[i] = getch();

			if ( temp_name[i] == 27 )
				return 27;
			else if ( temp_name[i] == 3 )
				return 3;
			else if ( temp_name[i] == 13 ) break;

			printf("%c", temp_name[i]);
		}
		temp_name[i] = '\0';

		for (int i = 0; i < strlen(temp_name); i++)
		{
			if ( ! (isalpha(temp_name[i]) || temp_name[i] == ' ') )
			{
				printf("\nthis is invalid name\n");
				printf("press any key to re-try\n");
				ch = getch();
				flag = 1;
				break;
			}
		}

		if ( flag == 0 )
		{
			strcpy(name, temp_name);
			return 0;
		}
	}

}

int get_gender(char gender[])
{
	char ch;
	char temp_gender[GENDER_WIDTH];

	while (1)
	{

		if ( ch == 27 )
			return 27;
		else if ( ch == 3 ) return 3;

		system("cls");
		display_add_patient_entry();
		printf("Enter the patient gender(male/female): ");

		int i;
		for (i = 0; i < GENDER_WIDTH + 1; i++)
		{
			temp_gender[i] = getch();

			if ( temp_gender[i] == 27 )
				return 27;
			else if ( temp_gender[i] == 3 )
				return 3;
			else if ( temp_gender[i] == 13 ) break;

			printf("%c", temp_gender[i]);
		}
		temp_gender[i] = '\0';

		if ( !strcmp(temp_gender, "male") || !strcmp(temp_gender, "female") )
		{
			strcpy(gender, temp_gender);
			return 0;
		}
		else
		{
			printf("\nnot valid\n");
			printf("enter any key to re-try");
			ch = getch();
		}

	}

}

int get_age(int *age)
{
	int temp_int = 0;
	char ch;
	while (1)
	{
		system("cls");
		display_add_patient_entry();
		printf("Enter the patient age: ");

		for (int i = 0; i < 3; i++)
		{
			ch = getch();

			if ( ch == 27 )
				return 27;
			else if ( ch == 3 ) return 3;

			printf("%c", ch);
			if ( isdigit(ch) )
			{
				temp_int = temp_int * 10 + ch - '0';
			}
			else if ( ch == 13 )
			{
				*age = temp_int;
				return 0;
			}
			else
			{
				printf("\n invaled number \n");
				printf("press any key to re-try\n");

				ch = getch();
				break;
			}
		}
	}
}
int add_patient_record(void)
{
	pat_data data; // to save the incoming data

	char state = 0;

	system("cls");
	display_add_patient_entry();

	state = get_id(data.ID);
	if ( state == 3 )
		return 3;
	else if ( state == 27 ) return 27;

	state = get_name(data.name);
	if ( state == 3 )
		return 3;
	else if ( state == 27 ) return 27;

	state = get_gender(data.gender);
	if ( state == 3 )
		return 3;
	else if ( state == 27 ) return 27;

	state = get_age(& (data.age));
	if ( state == 3 )
		return 3;
	else if ( state == 27 ) return 27;

	printf("the data entered is:\n");
	printf("\ndata id = %s\n", data.ID);
	printf("data name = %s\n", data.name);
	printf("data gender = %s\n", data.gender);
	printf("data age = %d\n", data.age);
	printf("press enter for confirm or any other key to discard\n");

	if ( getch() == 13 ) // '\r'
	{
		PatRec_Prepend(&Patients_record, data);
	}

	return 0;

}

int edit_patient_record(void)
{
	char ch;
	char temp_id[ID_WIDTH];

	while (1)
	{
		if ( ch == 27 )
			return 27;
		else if ( ch == 3 ) return 3;

		system("cls");
		display_edit_patient_entry();
		printf("Enter the patient ID: ");
		int i;

		for (i = 0; i < ID_WIDTH + 1; i++)
		{
			temp_id[i] = getch();

			if ( temp_id[i] == 27 )
				return 27;
			else if ( temp_id[i] == 3 )
				return 3;
			else if ( temp_id[i] == 13 ) break;

			printf("%c", temp_id[i]);
		}
		temp_id[i] = '\0';

		P_Node *edited_node = PatRec_search(Patients_record, temp_id);
		if ( edited_node )
		{
			char temp_ch;
			int dumb;
			while (1)
			{

				system("cls");
				display_edit_patient_entry();

				printf("which of the following fields you want to edit\n");
				printf("1- ID\n2- Name\n3- Gender\n4- age\n");
				temp_ch = getch();

				if ( temp_ch == 27 )
					return 27;
				else if ( temp_ch == 3 ) return 3;

				if ( temp_ch == '1' )
				{
					dumb = get_id(edited_node->patient.ID);
					if ( dumb == 3 )
						return 3;
					else if ( dumb == 27 )
						continue;
					else if ( dumb == 0 ) return 0;

				}

				else if ( temp_ch == '2' )
				{
					dumb = get_name(edited_node->patient.name);
					if ( dumb == 3 )
						return 3;
					else if ( dumb == 27 )
						continue;
					else if ( dumb == 0 ) return 0;

				}

				else if ( temp_ch == '3' )
				{
					dumb = get_gender(edited_node->patient.gender);
					if ( dumb == 3 )
						return 3;
					else if ( dumb == 27 )
						continue;
					else if ( dumb == 0 ) return 0;

				}

				else if ( temp_ch == '4' )
				{
					dumb = get_age(& (edited_node->patient.age));
					if ( dumb == 3 )
						return 3;
					else if ( dumb == 27 )
						continue;
					else if ( dumb == 0 ) return 0;

				}
				else
				{
					printf("No such choice try again\n");
					printf("press any key to proceed\n");
					getch();
				}
			}

		}
		else
		{
			if ( !check_id(temp_id) )
			{
				printf("\nThis is an invalid ID\n");
			}
			else
			{
				printf("\nthis ID not registered in the system\n");
			}
			printf("press any key to re-enter\n");
			ch = getch();
		}

	} // while(1)

}

int reserve_an_appontment(void)
{

	while (1)
	{
		char dumb;
		system("cls");
		display_reservations();
		printf("Enter the number of the desired time slot: ");
		dumb = getch();

		if ( dumb == 3 )
			return 3;
		else if ( dumb == 27 ) return 27;

		if ( isdigit(dumb) && dumb <= '5' && dumb >= '1' )
		{
			if ( slots_info[dumb - '0' - 1].state == 1 )
			{
				printf("\nthe required slot is not available\n");
				printf("press any key to choose again\n");
				getch();
			}
			else
			{
				while (1)
				{
					system("cls");
					display_reservations();
					printf("Enter the patient id: ");
					char temp_id[ID_WIDTH];

					if ( dumb == 3 )
						return 3;
					else if ( dumb == 27 ) return 27;

					int i;

					for (i = 0; i < ID_WIDTH + 1; i++)
					{
						temp_id[i] = getch();

						if ( temp_id[i] == 27 )
							return 27;
						else if ( temp_id[i] == 3 )
							return 3;
						else if ( temp_id[i] == 13 ) break;

						printf("%c", temp_id[i]);
					}
					temp_id[i] = '\0';

					if ( check_id(temp_id) )
					{
						if ( PatRec_search(Patients_record, temp_id) )
						{
							strcpy(slots_info[dumb - 1 - '0'].id_info, temp_id);
							slots_info[dumb - 1 - '0'].state = 1;
							return 0;
						}
						printf("\nthis ID is not registered in the system\n");
						printf("press any key to try again");
						getch();

					}
					else
					{
						printf("\ninvalid ID\n");
						printf("press any key to try again");
						getch();
					}
				} //while(1)

			}
		}
		else // case the used entered invalid slot number
		{
			printf("\nnot an option\n");
			printf("press any key to proceed\n");
			getch();
			continue;
		}
	}

}

int cancel_an_appontment()
{
	char dumb = 0;
	while (1)
	{
		system("cls");
		display_reservations();
		printf("Enter the patient id: ");
		char temp_id[ID_WIDTH];

		if ( dumb == 3 )
			return 3;
		else if ( dumb == 27 ) return 27;

		int i;

		for (i = 0; i < ID_WIDTH + 1; i++)
		{
			temp_id[i] = getch();

			if ( temp_id[i] == 27 )
				return 27;
			else if ( temp_id[i] == 3 )
				return 3;
			else if ( temp_id[i] == 13 ) break;

			printf("%c", temp_id[i]);
		}
		temp_id[i] = '\0';

		for (int i = 0; i < 5; i++)
		{
			if ( !strcmp(slots_info[i].id_info, temp_id) )
			{
				slots_info[i].state = 0;
				strcpy(slots_info[i].id_info, "    ");
				return 0;
			}
		}

		printf("there is no reservation with that id\n");
		printf("press any key to try again");
		getch();
	} //while(1)
}

int admin_mode()
{

	while (1)
	{
		system("cls");
		display_adminOptions();
		unsigned char option;
		option = getch();

		if ( option == 27 )
			return 27;
		else if ( option == 3 ) return 3;

		if ( option == '1' )
		{
			option = add_patient_record();
		}
		else if ( option == '2' )
		{
			option = edit_patient_record();
		}

		else if ( option == '3' )
		{
			option = reserve_an_appontment();
		}

		else if ( option == '4' )
		{
			option = cancel_an_appontment();
		}

		else if ( option == '5' )
		{
			PatRec_print(Patients_record);
			printf("press any key to continue");
			getch();
		}
		else
			continue;

		if ( option == 3 ) return 3;

	}
}

int view_patient_record(void)
{
	while (1)
	{
		system("cls");
		printf(
				"**************************************************[Esc]->return \n");
		printf(
				"                                                  [Ctrl+c]->Exit\n");
		printf("            Patient Record Viewer\n");
		printf("\n**************************************************\n");
		printf("Enter the patient id: ");
		char temp_id[ID_WIDTH];

		int i;

		for (i = 0; i < ID_WIDTH + 1; i++)
		{
			temp_id[i] = getch();

			if ( temp_id[i] == 27 )
				return 27;
			else if ( temp_id[i] == 3 )
				return 3;
			else if ( temp_id[i] == 13 ) break;

			printf("%c", temp_id[i]);
		}
		temp_id[i] = '\0';

		P_Node *patient = PatRec_search(Patients_record, temp_id);
		if ( patient )
		{
			printf("\n\nPatient name   = %s\n", patient->patient.name);
			printf("Patient ID     = %s\n", patient->patient.ID);
			printf("Patient gender = %s\n", patient->patient.gender);
			printf("Patient age    = %d\n", patient->patient.age);
			printf("\npress any key to proceed\n");
			getch();
			continue;

		}

		printf("\nthere is no Patient record with that id\n");
		printf("press any key to try again\n");
		getch();
	} //while(1)
}

int view_reservation_table()
{
	system("cls");
	display_reservations();
	printf("press any key to return\n");
	return getch();
}

int user_mode()
{
	while (1)
	{
		system("cls");
		display_userOptions();
		unsigned char option;
		option = getch();

		if ( option == 27 )
			return 27;
		else if ( option == 3 ) return 3;

		if ( option == '1' )
		{
			option = view_patient_record();
		}
		else if ( option == '2' )
		{
			option = view_reservation_table();
		}
		else
			continue;

		if ( option == 3 ) return 3;
	}
}

