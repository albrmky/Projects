/*
 * program.h
 *
 *  Created on: Jan 20, 2022
 *      Author: noureldeen albrmky
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

typedef struct
{
	char slot_name[8];
	char id_info[5];

	unsigned char state;
	unsigned char slot_number;
} reservation_slot;

void entry(void);
void admin_entry(void);
int get_password(void);
void display_reservations(void);

int user_mode();
int admin_mode();

void load_slots(void);
void save_slots(void);
void init_slots(void);
void print_slots(void);

#endif /* PROGRAM_H_ */
