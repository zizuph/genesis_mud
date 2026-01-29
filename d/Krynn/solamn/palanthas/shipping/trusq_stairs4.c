/*
 * Mortis 03.2006 
 *
 * The fourth floor of a winding staircase in a merchant estate
 */

#include "../local.h"
#include <macros.h>
#include CLOCKH

inherit SHIP_ROOMBASE;

string
query_to_jail()
{
	return "down";
}

void
reset_palan_room()
{
}

void
create_palan_room()
{
	object mdoor;

    SHORT("The fourth floor of a winding staircase in a merchant estate");
    LONG("Dark, oak paneling lines the walls of this small room from "
	+ "the ground up to three feet with polished, translucent white marble "
	+ "taking over from there.  A large, oak railed staircase winds down to "
	+ "the third floor from here, and an oak door leads east.\n");

	ITEM(({"wall", "walls", "panelling"}), "The bottom three feet of the "
	+ "walls in this room have been paneled in wide strips of dark stained "
	+ "oak.  From there up is polished, translucent white marble.  The "
	+ "paneling and marble are separated by a wide strip of oak trim.\n");
	ITEM("marble", "The marble in the room is translucent white and "
	+ "polished to a gleaming shine.\n");
	ITEM("floor", "The floor is made of large sheets of translucent white "
	+ "marble and polished to a shine.  A large staircase descends "
	+ "through it.\n");
	ITEM("ceiling", "The ceiling has been finished with "
	+ "translucent white marble.  A large staircase rises into it.\n");
	ITEM("trim", "A wide strim of oak trim separates the paneling from the "
	+ "marble.\n");
	ITEM(({"stairs", "staircase"}), "A large staircase with oak railing "
	+ "winds up down to the third floor from here.  It is dark stained and "
	+ "very ornately carved.\n");

	add_smell("vampire", "The air is clean, but you smell expensive perfumes "
	+ "east.  Your fangs throb with anticipation as you sense hot "
	+ "blood pumping through a great many hearts closeby.");
	add_smell("morgul", "The air is clean, but you smell expensive perfumes "
	+ "east.");
	add_smell("human", "The air is clean, but you smell expensive perfumes "
	+ "east.");
	add_smell("elf", "The air is clean, but you smell human perfumes "
	+ "east.");
	add_smell("goblin", "The air is clean, but you smell perfumie things "
	+ "east.");
	add_smell("dwarf", "The air is clean, but you human perfumes "
	+ "east.");
	add_smell("hobbit", "The air is clean, but you smell expensive perfumes "
	+ "east.");
	add_smell("gnome", "The air is clean, but you detect expensive perfumes "
	+ "east.");
	add_smell("minotaur", "The air is clean, but you smell expensive perfumes "
	+ "east.  The smell of man is thick here.");
	add_smell("halfhuman", "The air is clean, but you smell expensive "
	+ "perfumes east.");
	add_smell("halfelf", "The air is clean, but you smell expensive perfumes "
	+ "east.");
	add_smell("orc", "The smell of arms perfumes in the sterile air "
	+ "cannot mask the scent of so much manflesh in this place.");
	add_smell("hobgoblin", "The clean air would indicate humans keep this "
	+ "place well tended.  You smell human perfumes east.");
	add_smell("kender", "The air is clean, but you smell pretty perfumes "
	+ "east.");
	add_smell("drow", "The sterile air here would indicate the place is "
	+ "clean by human standards.  You detect the smells of human perfumes "
	+ "east.");
	add_smell("noldor", "The air is clean, but you smell human perfumes "
	+ "east.");
	add_smell("uruk", "The smell of human perfumes in the sterile air "
	+ "cannot mask the scent of so much manflesh in this place.");
	add_smell("presence", "You don't pick up much in your current state.");
	add_smell("unknown", "The air is clean and smells of expensive perfumes, "
	+ "but what the heck race are you?!?  Why not mail Krynn for fun?");

	mdoor = clone_object(SHIP + "doors/trusq_master_door1");
	mdoor->move(TO);

	EXIT(SHIP + "trusq_stairs3", "down", 0, 0);

	reset_palan_room();
}
