/*
 * Mortis 03.2006 
 *
 * The business offices of merchant house Trusq.
 */

#include "../local.h"
#include <macros.h>
#include CLOCKH

inherit SHIP_ROOMBASE;

string
query_to_jail()
{
	return "west";
}

object acc1, acc2, acc3, acc4;

void
reset_palan_room()
{
	if (!acc1)
	{
		acc1 = clone_object(SHIP + "living/trusq_accountant");
		acc1->move(TO);
	}
	if (!acc2)
	{
		acc2 = clone_object(SHIP + "living/trusq_accountant");
		acc2->move(TO);
	}
	if (!acc3)
	{
		acc3 = clone_object(SHIP + "living/trusq_accountant");
		acc3->move(TO);
	}
	if (!acc4)
	{
		acc4 = clone_object(SHIP + "living/trusq_accountant");
		acc4->move(TO);
	}
}

void
create_palan_room()
{
	object offdoor;

    SHORT("A large office in a merchant estate");
    LONG("Dark, oak paneling lines the walls of this large office from "
	+ "the ground up to three feet with polished, translucent white marble "
	+ "taking over from there.  The office is filled with desks, cabinets "
	+ "of files, office workers busy about their paperwork, and takes up "
	+ "almost the entire second floor except for a private office in the "
	+ "southeast corner.\n");

	ITEM("office", "You are in the office.  Have a <look> around?\n");
	ITEM(({"wall", "walls", "panelling"}), "The bottom three feet of the "
	+ "walls in this room have been paneled in wide strips of dark stained "
	+ "oak.  From there up is polished, translucent white marble.  The "
	+ "paneling and marble are separated by a wide strip of oak trim.\n");
	ITEM("marble", "The marble in the room is translucent white and "
	+ "polished to a gleaming shine.\n");
	ITEM("floor", "The floor is made of large sheets of translucent white "
	+ "marble and polished to a shine.\n");
	ITEM("ceiling", "The ceiling has been finished with translucent white "
	+ "marble.\n");
	ITEM("trim", "A wide strim of oak trim separates the paneling from the "
	+ "marble.\n");
	ITEM(({"stairs", "staircase"}), "A large staircase with oak railing "
	+ "is west of here.\n");
	ITEM(({"desk", "desks", "cabinet", "cabinets", "file", "files",
	  "paperwork"}), "The office is filled with oak desks, tall cabinets "
	+ "with drawers full of files and invoices, and paperwork of all sorts "
	+ "arranged neatly here and there.\n");

	add_smell("vampire", "The air is clean, but you smell ink and old, dry "
	+ "paper here.  Your fangs throb with anticipation as you sense hot "
	+ "blood pumping through a great many hearts closeby.");
	add_smell("morgul", "The air is clean, but you smell ink and old, dry "
	+ "paper here.  The ink is quality and the paper well-kept.");
	add_smell("human", "The air is clean, but you smell ink and old, dry "
	+ "paper here.");
	add_smell("elf", "The air is clean, but you smell ink and old, dry "
	+ "paper here.");
	add_smell("goblin", "The air is clean, but you smell old, dry things "
	+ "here.");
	add_smell("dwarf", "The air is clean, but you smell ink and old, dry "
	+ "paper here.");
	add_smell("hobbit", "The air is clean, but you smell ink and old, dry "
	+ "paper here.");
	add_smell("gnome", "The air is clean, but you detect ink and old, dry "
	+ "paper here.  The ink is quality and the paper well-kept.");
	add_smell("minotaur", "The air is clean, but you smell ink and old, dry "
	+ "paper here.  The smell of man is thick here.");
	add_smell("halfhuman", "The air is clean, but you smell ink and old, dry "
	+ "paper here.");
	add_smell("halfelf", "The air is clean, but you smell ink and old, dry "
	+ "paper here.");
	add_smell("orc", "The smell of old, dry things in the sterile air cannot "
	+ "mask the scent of so much manflesh in this place.");
	add_smell("hobgoblin", "The clean air would indicate humans keep this "
	+ "place well tended.  You smell ink and paper here.");
	add_smell("kender", "The air is clean, but you smell ink and old, dry "
	+ "paper here.");
	add_smell("drow", "The sterile air here would indicate the place is "
	+ "clean by human standards.  You detect the smells of ink and old, dry "
	+ "paper eaherest.");
	add_smell("noldor", "The air is clean, but you smell ink and old, dry "
	+ "paper here.");
	add_smell("uruk", "The smell of old, dry things in the sterile air "
	+ "cannot mask the scent of so much manflesh in this place.");
	add_smell("presence", "You don't pick up much in your current state.");
	add_smell("unknown", "The air is clean and smells of ink and paper, but "
	+ "what the heck race are you?!?  Why not mail Krynn for fun?");

	offdoor = clone_object(SHIP + "doors/trusq_office_door1");
	offdoor->move(TO);

	EXIT(SHIP + "trusq_stairs2", "west", 0, 0);

	reset_palan_room();
}
