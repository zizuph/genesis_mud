/* 
 * Laethorian Spa and Body, Massage foyer
 *
 * Mortis 02.2006
 *
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit NOBLE_ROOMBASE;

string
query_to_jail()
{
  return "west";
}


void
reset_palan_room()
{

}

void
create_palan_room()
{
    SHORT("Massage foyer in a dayspa");
    LONG("This foyer is bright and clean with tall, silver braziers burning "
	+ "in each of its four corners.  The place is completely done in "
	+ "polished, translucent white marble.  A wide hallway leads west to an "
	+ "intersection while arched doorways lead north and south.  A marble "
	+ "sign hangs on the east wall.\n");

	ITEM(({"spa", "dayspa"}), "The spa is quiet and clean.  Your footsteps "
	+ "echo down the hallways.  Have a <look> around.\n");
	ITEM("foyer", "The foyer is quiet and clean.  Your footsteps  echo down "
	+ "the hallways.  Have a <look> around.\n");
	ITEM(({"brazier", "braziers", "silver brazier", "silver braziers", "fire",
		"fires"}), "Tall, silver braziers stand in the four corners of this "
	+ "foyer.  Small fires burn in each, their light reflecting off the "
	+ "polished marble of the ceiling and shedding even light across the "
	+ "floor and walls.\n");
	ITEM(({"corner", "corners"}), "Standing in each of the corners and "
	+ "providing light are tall, silver braziers.\n");
	ITEM(({"wall", "walls", "ceiling", "floor", "floors"}), "The walls and "
	+ "ceiling are of translucent white marble polished to a gleaming "
	+ "shine.  A marble sign hangs on the east wall.\n");
	ITEM(({"marble sign", "sign", "east sign"}), "A marble sign with black "
	+ "lettering done in the old style hangs on the east wall.  You may "
	+ "<read> it.\n");
	ITEM(({"arched doorway", "arched doorways", "doorway", "doorway"}),
	  "Small, arched doorways lead north and south from here to rooms not "
	+ "much larger than this foyer.\n");
	ITEM(({"hallway", "hall"}), "A wide hallway leads east to an "
	+ "intersection.\n");

    add_smell("vampire", "The air here is cool, clean, and flooded with "
	+ "smells subduing the scent of human blood.  The smell of fragrant oils "
	+ "comes from the north and south doorways, and further west the air "
	+ "is moist and warm.");
    add_smell("morgul", "The air here is cool and clean.  The smell of "
	+ "fragrant oils comes from the north and south doorways, and further "
	+ "west the air is moist and warm.");
    
	add_smell("human", "The air here is cool and clean.  The smell of "
	+ "fragrant oils comes from the north and south doorways, and further "
	+ "west the air is moist and warm.");
	add_smell("elf", "The air here is cool and clean.  The smell of fragrant "
	+ "oils comes from the north and south doorways, and further west, where "
	+ "the air is moist and warm, your keen nose detects an indoor pool of "
	+ "water.");
	add_smell("goblin", "The air here is cool and clean.  The smell of "
	+ "fragrant oils comes from the north and south doorways, and further "
	+ "west the air is moist and warm.");
	add_smell("dwarf", "The air here is cool and clean.  The smell of fragrant "
	+ "oils comes from the north and south doorways, and further west, where "
	+ "the air is moist and warm, you pick up the scent of an indoor pool of "
	+ "water.");
	add_smell("hobbit", "The air here is cool and clean.  The smell of "
	+ "fragrant oils comes from the north and south doorways, and further "
	+ "west the air is moist and warm.");
	add_smell("gnome", "The air here is cool and clean.  To the west you "
	+ "believe you detect moisture indicative of an indoor body of water, "
	+ "and north and south fragrant oils commonly used by humans in "
	+ "massaging.");
	add_smell("minotaur", "Soapy, fragrant oils and odours designed to mask "
	+ "the scent of humans flood the cool, clean air here while to the west "
	+ "you detect moisture from an indoor pools.");
	add_smell("halfhuman", "The air here is cool and clean.  From the west "
	+ "you pick up the smells of an indoor pool, and to the north and south "
	+ "you smell fragrant oils.");
	add_smell("halfelf", "The air here is cool and clean.  From the west "
	+ "you pick up the smells of an indoor pool, and to the north and south "
	+ "you smell fragrant oils.");
	add_smell("orc", "The scent of manflesh tainted with flowery oils, "
	+ "floods your nostrils.  Further west the air is warm and moist.");
	add_smell("hobgoblin", "The air here is clean and cool.  From the north "
	+ "and south you smell fragrant oils.  Further west, the air is warm "
	+ "and moist.");
	add_smell("kender", "Hmm!  The scents of fragrant oils waft in "
	+ "pleasantly from the north and south while to the west the air is warm "
	+ "and moist like an indoor pool is nearby.");
	add_smell("drow", "The air here is cool and clean.  The smell of fragrant "
	+ "oils comes from the north and south doorways, and further west, where "
	+ "the air is moist and warm, your keen nose detects an indoor pool of "
	+ "water.");
	add_smell("noldor", "The air here is cool and clean.  The smell of fragrant "
	+ "oils comes from the north and south doorways, and further west, where "
	+ "the air is moist and warm, your keen nose detects an indoor pool of "
	+ "water.");

	CMD(({"marble sign", "sign", "east sign"}), "read", "@@read_sign");

	EXIT(NOBLE + "spa_massagem", "north", 0, 0);
	EXIT(NOBLE + "spa_massagef", "south", 0, 0);
	EXIT(NOBLE + "spa2", "west", 0, 0);
	
	reset_palan_room();
}

public int
read_sign()
{
	say(QCTNAME(TP) + " studies the marble sign on the east wall.\n");
	write("The sign reads...\n");
	cat(NOBLE + "obj/spamassage.txt", 1, 50);

	return 1;
}
