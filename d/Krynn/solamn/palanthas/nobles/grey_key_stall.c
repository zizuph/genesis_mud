/* Mortis 11.2005
 *
 * The place where Greystone keys are kept.
 */

#include "../local.h"
#include <macros.h>

inherit NOBLE_BASE;

#define KEY1		NOBLE + "obj/grey_key1"
#define KEY2		NOBLE + "obj/grey_key2"
#define KEY3		NOBLE + "obj/grey_key3"
#define KEY4		NOBLE + "obj/grey_key4"
#define KEY5		NOBLE + "obj/grey_key5"

object k1, k2, k3, k4, k5;

void
reset_palan_room()
{
	if (k5) { write("They's uh key5.\n"); }
	else { k5 = clone_object(KEY5); k5->move(TO, 1); }

	if (k4) { write("They's uh key4.\n"); }
	else { k4 = clone_object(KEY4); k4->move(TO, 1); }

	if (k3) { write("They's uh key3.\n"); }
	else { k3 = clone_object(KEY3); k3->move(TO, 1); }

	if (k2) { write("They's uh key2.\n"); }
	else { k2 = clone_object(KEY2); k2->move(TO, 1); }

	if (k1) { write("They's uh key1.\n"); }
	else { k1 = clone_object(KEY1); k1->move(TO, 1); }
}

void
create_palan_room()
{
	set_short("Where keys come from");
	set_long("This is where grey Greystone Inn's unique keys are made.\n");


	add_exit(NOBLE + "greystone.c","out");

/*	clone_object(NOBLE + "obj/grey_key5")->move(TO, 1);
	clone_object(NOBLE + "obj/grey_key4")->move(TO, 1);
	clone_object(NOBLE + "obj/grey_key3")->move(TO, 1);
	clone_object(NOBLE + "obj/grey_key2")->move(TO, 1);
	clone_object(NOBLE + "obj/grey_key1")->move(TO, 1);*/

	reset_palan_room();
}

