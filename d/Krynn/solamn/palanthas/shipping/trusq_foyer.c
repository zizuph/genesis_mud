/* Mortis 12.2005 
 *
 */

#include "../local.h"
#include <macros.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>
#include <living_desc.h>
#include <formulas.h>
#include CLOCKH

#define VIEWSTREET				(SHIP + "s03")

inherit SHIP_ROOMBASE;

string
query_to_jail()
{
  return "north";
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
    SHORT("In the well furnished foyer of a merchant estate");
    LONG("Dark, oak paneling lines the walls of this ten by ten foyer from "
	+ "the ground up to three feet with polished, translucent white marble "
	+ "taking over from there.  A wide strip of oak trim separates the "
	+ "paneling from the marble, and arranged upon it are vases of "
	+ "flowers, statuettes, and busts.  A wide door with a pointed arch "
	+ "is in the center of the north wall with windows to either side, "
	+ "and a large hall is to the south.\n");

	ITEM("foyer", "You are in the foyer.  Have a <look> around?\n");
	ITEM(({"gravel", "gravel street", "wide gravel street", "wide street"}),
	  "Through the windows you see small piece, crushed marble that has been "
	+ "raked perfectly level on the wide street leading north from this "
	+ "estate to Bulwark Round.\n");
	ITEM(({"wall", "walls", "panelling"}), "The bottom three feet of the "
	+ "walls in this foyer have been paneled in wide strips of dark stained "
	+ "oak.  From there up is polished, translucent white marble.  The "
	+ "paneling and marble are separated by a wide strip of oak trim.\n");
	ITEM("marble", "The marble in the foyer is translucent white and "
	+ "polished to a gleaming shine.\n");
	ITEM("floor", "The floor is made of large blocks of translucent white "
	+ "marble, polished to a shine, and topped with a circular rug.  The "
	+ "rug is yellow on one side and light blue on the other.\n");
	ITEM("rug", "A circular rug lays on the floor here.  One side is yellow "
	+ "while the other is light blue.\n");
	ITEM("ceiling", "The ceiling has been finished with "
	+ "translucent white marble.\n");
	ITEM("trim", "A wide strim of oak trim separates the paneling from the "
	+ "marble.  Arranged upon it are vases of flowers, statuettes, and "
	+ "busts.\n");
	ITEM(({"vase", "vases", "flower", "flowers", "statuette", "statuettes",
		"bust", "busts"}), "Artfully arranged upon the wide strip of oak "
	+ "trim circling the room along the walls are glazed white and grey "
	+ "vases of roses, sunflowers, and lilies, small marble statuettes of "
	+ "nude athletes in sporting poses, and marble busts of a weathered "
	+ "old bearded man and a prim woman.\n");
	ITEM("door", "A wide door covered with squares carved into it, each "
	+ "containing a swirling sun, leads north out of the estate.  It has "
	+ "been stained dark and has a pointed arch.  To either side is a "
	+ "window looking out onto the street.\n");
	ITEM(({"window", "windows"}), "Windows on either side of the door in "
	+ "the north look out onto the gravel covered street leading out of "
	+ "the estate.  You may <view street> from here.\n");

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

	CMD(({"north", "n", "street"}), "view", "@@view_street");

	EXIT(SHIP + "s03", "north", 0, 0);
	EXIT(SHIP + "trusq_hall", "south", 0, 0);

	reset_palan_room();
}

int
view_street()
{
	/* This function returns an equivalent of 'look' from s03
	 * most importantly without any supporting code from the
	 * target room.
	 */

	object *inv, *obs, *ppl, target;
    string desc;

	write(VIEWSTREET->long());
	target = find_object(VIEWSTREET);
	inv = all_inventory(target);
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
	ppl = FILTER_LIVE(inv);

	if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
	write(one_of_list(({"Through the windows you see "}))
						+ desc + " on the ground.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write(one_of_list(({"You can see "}))
						+ desc + " outside the estate.\n");
 
	return 1;
}
