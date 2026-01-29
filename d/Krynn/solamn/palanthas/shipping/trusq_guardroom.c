/*
 * Mortis 03.2006 
 *
 * The main guardroom of merchant house Trusq.
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

object guard1, guard2, guard3, guard4;

void
reset_palan_room()
{
	if (!guard1)
	{
		guard1 = clone_object(SHIP + "living/trusq_guard");
		guard1->move(TO);
	}
	if (!guard2)
	{
		guard2 = clone_object(SHIP + "living/trusq_guard");
		guard2->move(TO);
	}
	if (!guard3)
	{
		guard3 = clone_object(SHIP + "living/trusq_guard");
		guard3->move(TO);
	}
	if (!guard4)
	{
		guard4 = clone_object(SHIP + "living/trusq_guard");
		guard4->move(TO);
	}
}

void
create_palan_room()
{
	object offdoor;

    SHORT("The guard quarters suite of a merchant estate");
    LONG("Dark, oak paneling lines the walls of this large office from "
	+ "the ground up to three feet with polished, translucent white marble "
	+ "taking over from there.  The suite is filled with bunks, shelves, "
	+ "racks of arms, and takes up almost the entire third floor except "
	+ "for a private room in the southeast corner.\n");

	ITEM(({"suite", "quarters"}), "You are in the guard quarters suite.  "
	+ "Have a <look> around?\n");
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
	ITEM(({"bunk", "bunks", "shelf", "shelves", "rack", "racks", "arm",
	  "arms", "effects", "gear", "oil", "oils", "rag", "rags"}),
	  "The guard quarters suite is lined with rows of bunks "
	+ "with neatly made grey wool blankets, shelves of personal effects, "
	+ "and wooden racks for storing gear along with cleaning oils and "
	+ "rags.\n");

	add_smell("vampire", "The air is clean, but you smell arms oil and "
	+ "leather here.  Your fangs throb with anticipation as you sense hot "
	+ "blood pumping through a great many hearts closeby.");
	add_smell("morgul", "The air is clean, but you smell arms oil and "
	+ "leather here.");
	add_smell("human", "The air is clean, but you smell arms oil and "
	+ "leather here.");
	add_smell("elf", "The air is clean, but you smell arms oil and "
	+ "leather here.");
	add_smell("goblin", "The air is clean, but you smell arms oil and "
	+ "leather here.");
	add_smell("dwarf", "The air is clean, but you smell arms oil and "
	+ "leather here.");
	add_smell("hobbit", "The air is clean, but you smell ink and old, dry "
	+ "paper here.");
	add_smell("gnome", "The air is clean, but you detect arms oil and "
	+ "leather here.");
	add_smell("minotaur", "The air is clean, but you smell arms oil and "
	+ "leather here.  The smell of man is thick here.");
	add_smell("halfhuman", "The air is clean, but you smell arms oil and "
	+ "leather here.");
	add_smell("halfelf", "The air is clean, but you smell arms oil and "
	+ "leather here.");
	add_smell("orc", "The smell of arms oil and leather in the sterile air "
	+ "cannot mask the scent of so much manflesh in this place.");
	add_smell("hobgoblin", "The clean air would indicate humans keep this "
	+ "place well tended.  You smell arms oil and leather here.");
	add_smell("kender", "The air is clean, but you smell arms oil and "
	+ "leather here.");
	add_smell("drow", "The sterile air here would indicate the place is "
	+ "clean by human standards.  You detect the smells of arms oil and "
	+ "leather here.");
	add_smell("noldor", "The air is clean, but you smell arms oil and "
	+ "leather here.");
	add_smell("uruk", "The smell of arms oil and leather in the sterile air "
	+ "cannot mask the scent of so much manflesh in this place.");
	add_smell("presence", "You don't pick up much in your current state.");
	add_smell("unknown", "The air is clean and arms oil and leather, but "
	+ "what the heck race are you?!?  Why not mail Krynn for fun?");

	offdoor = clone_object(SHIP + "doors/trusq_guardroom_door1");
	offdoor->move(TO);

	EXIT(SHIP + "trusq_stairs3", "west", 0, 0);

	reset_palan_room();
}
