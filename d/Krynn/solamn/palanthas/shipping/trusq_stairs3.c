/*
 * Mortis 03.2006 
 *
 * The third floor of a winding staircase in a merchant estate
 */

#include "../local.h"
#include <macros.h>
#include CLOCKH

inherit SHIP_ROOMBASE;

/* Prototypes */
int stairs_guards();

string
query_to_jail()
{
	return "down";
}

object guard1, guard2;

void
reset_palan_room()
{
	if (!guard1)
	{
		guard1 = clone_object(SHIP + "living/trusq_guard2");
		guard1->move(TO);
	}

	if (!guard2)
	{
		guard2 = clone_object(SHIP + "living/trusq_guard2");
		guard2->move(TO);
	}
}

void
create_palan_room()
{
    SHORT("The third floor of a winding staircase in a merchant estate");
    LONG("Dark, oak paneling lines the walls of this small room from "
	+ "the ground up to three feet with polished, translucent white marble "
	+ "taking over from there.  A large, oak railed staircase winds up to "
	+ "the fourth floor, and down to the second here, and to the east is a "
	+ "hall.\n");

	ITEM("hall", "There is a hall east of you.  Try <east> to check it "
	+ "out.\n");
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
	+ "winds up to the fourth floor and down to the second from here.  It is "
	+ "dark stained and very ornately carved.\n");

	add_smell("vampire", "The air is clean, but you smell arms oil and "
	+ "leather east.  Your fangs throb with anticipation as you sense hot "
	+ "blood pumping through a great many hearts closeby.");
	add_smell("morgul", "The air is clean, but you smell arms oil and "
	+ "leather east.");
	add_smell("human", "The air is clean, but you smell arms oil and "
	+ "leather east.");
	add_smell("elf", "The air is clean, but you smell arms oil and "
	+ "leather east.");
	add_smell("goblin", "The air is clean, but you smell arms oil and "
	+ "leather east.");
	add_smell("dwarf", "The air is clean, but you smell arms oil and "
	+ "leather east.");
	add_smell("hobbit", "The air is clean, but you smell ink and old, dry "
	+ "paper east.");
	add_smell("gnome", "The air is clean, but you detect arms oil and "
	+ "leather east.");
	add_smell("minotaur", "The air is clean, but you smell arms oil and "
	+ "leather east.  The smell of man is thick here.");
	add_smell("halfhuman", "The air is clean, but you smell arms oil and "
	+ "leather east.");
	add_smell("halfelf", "The air is clean, but you smell arms oil and "
	+ "leather east.");
	add_smell("orc", "The smell of arms oil and leather in the sterile air "
	+ "cannot mask the scent of so much manflesh in this place.");
	add_smell("hobgoblin", "The clean air would indicate humans keep this "
	+ "place well tended.  You smell arms oil and leather east.");
	add_smell("kender", "The air is clean, but you smell arms oil and "
	+ "leather east.");
	add_smell("drow", "The sterile air here would indicate the place is "
	+ "clean by human standards.  You detect the smells of arms oil and "
	+ "leather east.");
	add_smell("noldor", "The air is clean, but you smell arms oil and "
	+ "leather east.");
	add_smell("uruk", "The smell of arms oil and leather in the sterile air "
	+ "cannot mask the scent of so much manflesh in this place.");
	add_smell("presence", "You don't pick up much in your current state.");
	add_smell("unknown", "The air is clean and smells of arms oil and "
	+ "leather, but what the heck race are you?!?  Why not mail Krynn for "
	+ "fun?");

	EXIT(SHIP + "trusq_guardroom", "east", 0, 0);
	EXIT(SHIP + "trusq_stairs4", "up", "@@stairs_guards", 0);
	EXIT(SHIP + "trusq_stairs2", "down", 0, 0);

	reset_palan_room();
}

int
stairs_guards()
{
	if (!guard1 && !guard2)
		return 0;

	write("A security guard bars passage up to the fourth floor saying:  "
	+ "The private Trusq suite is off limits to visitors.  Stand down.\n");
	say(QCTNAME(TP) + " is barred passage up to the fourth floor by a "
	+ "security guard who says:  The private Trusq suite is off limits to "
	+ "visitors.  Stand down.\n");
	return 1;
}
