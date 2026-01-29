/*
 * Mortis 12.2005 
 *
 * The bottom of a winding staircase in a merchant estate
 */

#include "../local.h"
#include <macros.h>
#include CLOCKH

inherit SHIP_ROOMBASE;

string
query_to_jail()
{
	return "east";
}

object guard1, guard2;

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
}

void
create_palan_room()
{
    SHORT("The bottom of a winding staircase in a merchant estate");
    LONG("Dark, oak paneling lines the walls of this small room from "
	+ "the ground up to three feet with polished, translucent white marble "
	+ "taking over from there.  A large, oak railed staircase winds up to "
	+ "the next floor here, and to the east is a large hall.\n");

	ITEM(({"wall", "walls", "panelling"}), "The bottom three feet of the "
	+ "walls in this room have been paneled in wide strips of dark stained "
	+ "oak.  From there up is polished, translucent white marble.  The "
	+ "paneling and marble are separated by a wide strip of oak trim.\n");
	ITEM("marble", "The marble in the room is translucent white and "
	+ "polished to a gleaming shine.\n");
	ITEM("floor", "The floor is made of large blocks of translucent white "
	+ "marble and polished to a shine.\n");
	ITEM("ceiling", "The ceiling has been finished with "
	+ "translucent white marble.  A large staircase rises into it.\n");
	ITEM("trim", "A wide strim of oak trim separates the paneling from the "
	+ "marble.\n");
	ITEM(({"stairs", "staircase"}), "A large staircase with oak railing "
	+ "winds up to the second floor from here.  It is dark stained and "
	+ "very ornately carved.\n");

	add_smell("vampire", "The air is clean and fragranced with the scents of "
	+ "freshly cut roses, sunflowers, and lilies.  Your fangs throb with "
	+ "anticipation as you sense hot blood pumping through a great many "
	+ "hearts further in.");
	add_smell("morgul", "The air is clean and fragranced with the scents of "
	+ "fresh flowers.");
	add_smell("human", "The air is clean and fragranced with the scents of "
	+ "fresh flowers.");
	add_smell("elf", "The air is clean and fragranced with the scents of "
	+ "freshly cut roses, sunflowers, and lilies.");
	add_smell("goblin", "The air is odourless except for the sickly smells "
	+ "of flowery things.");
	add_smell("dwarf", "The air is clean and fragranced with the scents of "
	+ "fresh flowers.");
	add_smell("hobbit", "The air here is clean in an indoor sort of way and "
	+ "fragranced with the scents of fresh roses, sunflowers, and lilies.  "
	+ "If you're not mistaken, there must be a kitchen further in, but "
	+ "there's only one way to be sure.");
	add_smell("gnome", "The air is clean, not stale, and fragranced with the "
	+ "scents of fresh flowers.");
	add_smell("minotaur", "The scent of flowers in the clean air cannot mask "
	+ "the smells of man within.");
	add_smell("halfhuman", "The air is clean and fragranced with the scents of "
	+ "fresh flowers.");
	add_smell("halfelf", "The air is clean and fragranced with the scents of "
	+ "freshly cut roses, sunflowers, and lilies.");
	add_smell("orc", "The scent of flowers in the sterile air cannot mask "
	+ "the scent of so much manflesh in this place.");
	add_smell("hobgoblin", "The clean air would indicate humans keep this "
	+ "place well tended.  You smell fresh flowers here as well.");
	add_smell("kender", "The air here is nice and clean and fragranced with "
	+ "the scents of fresh flowers, but you're also somewhat sure there is a "
	+ "kitchen deeper in, but there are only a few ways to find out and only "
	+ "one worth trying.");
	add_smell("drow", "The sterile air here would indicate the place is "
	+ "clean by human standards.  You detect the scents of freshly cut, "
	+ "overworld flowers.");
	add_smell("noldor", "The air is clean by human standards and fragranced "
	+ "with the scents of freshly cut roses, sunflowers, and lilies.");
	add_smell("uruk", "The scent of flowers in the sterile air cannot mask "
	+ "the scent of so much manflesh in this place.");
	add_smell("presence", "You don't pick up much in your current state.");
	add_smell("unknown", "The air is clean and fragranced with flowers, but "
	+ "what the heck race are you?!?  Why not mail Krynn for fun?");

	EXIT(SHIP + "trusq_hall", "east", 0, 0);
	EXIT(SHIP + "trusq_stairs2", "up", 0, 0);

	reset_palan_room();
}
