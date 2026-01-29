/* 
 * Mortis 03.2006
 *
 * Inside chimney on roof of merchant house Trusq.
 *
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <ss_types.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>

#define TRUSQ_ROOF				SHIP + "trusq_roof"
#define CHIMNEY_INVADER			"_i_invaded_trusq_through_the_chimney"
#define FOUND_FIREPLACE_HOLE	"_i_found_trusq_fireplace_hole"

inherit SHIP_ROOMBASE;

void
reset_palan_room()
{
}

void
create_palan_room()
{
    SHORT("In a wide brick chimney below its dark shingled roof");
    LONG("Oily soot coats the bricks inside this cramped chimney.  A dark "
	+ "shingled roof over the chimney keeps the rain from falling down "
	+ "the chimney while letting the smoke out.  Down below is a "
	+ "fireplace opening into a large suite.\n");

	ITEM("suite", "The suite is through the fireplace from here.\n");
	ITEM("chimney", "You are in the chimney.  Have a <look> around?\n");
	ITEM(({"fire", "fireplace"}), "A brick fireplace is below you."
	+ "@@exa_fire@@" + "\n");
	ITEM(({"ash", "ashes"}), "Ashes from spent fires lay scattered in the "
	+ "fireplace below.\n");
	ITEM("vent", "@@exa_vent");
	ITEM("soot", "Thick, oily soot coats the bricks inside this cramped "
	+ "chimney.  It's getting all over you.\n");
	ITEM(({"brick", "bricks"}), "The bricks are completely coated in oily "
	+ "soot.\n");
	ITEM(({"roof", "shingle", "shingles"}), "A dark shingled roof covers "
	+ "the chimney preventing rain from falling inside while allowing "
	+ "smoke to escape.  You can peek out from beneath it with <view "
	+ "roof>.\n");

	add_smell("vampire", "The smells of ash, spent wood, and the sooty "
	+ "residues of cooking are strong here.  Your fangs throb with "
	+ "anticipation as you sense hot blood pumping through a great many "
	+ "hearts close by.");
	add_smell("morgul", "The smells of ash, spent wood, and the sooty "
	+ "residues of cooking are strong here, reminiscent of a burned out "
	+ "body pyre.");
	add_smell("human", "The smells of ash, spent wood, and the sooty "
	+ "residues of cooking are strong here.");
	add_smell("elf", "The smells of ash, spent wood, and the sooty "
	+ "residues of cooking are strong here.");
	add_smell("goblin", "The smells of ash, spent wood, and the sooty "
	+ "residues of cooking are strong here.");
	add_smell("dwarf", "The smells of ash, spent wood, and the sooty "
	+ "residues of cooking are strong here.");
	add_smell("hobbit", "The smells of ash, spent wood, and the sooty "
	+ "residues of cooking are strong here.");
	add_smell("gnome", "The smells of ash, spent wood, and the sooty "
	+ "residues of cooking are strong here.");
	add_smell("minotaur", "The smells of ash, spent wood, and the sooty "
	+ "residues of cooking are strong here.");
	add_smell("halfhuman", "The smells of ash, spent wood, and the sooty "
	+ "residues of cooking are strong here.");
	add_smell("halfelf", "The smells of ash, spent wood, and the sooty "
	+ "residues of cooking are strong here.");
	add_smell("orc", "The smells of ash, spent wood, and the sooty "
	+ "residues of cooking are strong here, reminiscent of a burned out "
	+ "body pyre.");
	add_smell("hobgoblin", "The smells of ash, spent wood, and the sooty "
	+ "residues of cooking are strong here.");
	add_smell("kender", "The smells of ash, spent wood, and the sooty "
	+ "residues of cooking are strong here.");
	add_smell("drow", "The smells of ash, spent wood, and the sooty "
	+ "residues of cooking are strong here.");
	add_smell("noldor", "The smells of ash, spent wood, and the sooty "
	+ "residues of cooking are strong here.");
	add_smell("uruk", "The smells of ash, spent wood, and the sooty "
	+ "residues of cooking are strong here, reminiscent of a burned out "
	+ "body pyre.");
	add_smell("presence", "You don't pick up much in your current state.");
	add_smell("unknown", "The air is sooty and ashy smelling, but "
	+ "what the heck race are you?!?  Why not mail Krynn for fun?");

	CMD(({"out", "roof"}), "view", "@@view_roof");

	EXIT(SHIP + "trusq_roof", "up", 0, 0);
	EXIT(SHIP + "trusq_master", "down", "@@chimney_to_suite", 0);

	reset_palan_room();
}

string
exa_fire()
{
	if (TP->query_prop(FOUND_FIREPLACE_HOLE) == 1)
		return "  Behind the ash in the back of the fireplace is a vent "
		+ "where smoke from the fires rises through here and up the "
		+ "chimney.";

	if (TP->query_skill(SS_AWARENESS) > 20 + random(20))
	{
		TP->add_prop(FOUND_FIREPLACE_HOLE, 1);
		return "  You discover a large vent behind the ash in the back of "
		+ "the fireplace where smoke from the fires rises through here and "
		+ "up the chimney.";
	}
	return "";
}

string
exa_vent()
{
	if (TP->query_prop(FOUND_FIREPLACE_HOLE) != 1)
		return "Examine what?\n";

	return "You're in the vent.  Have a <look> around?\n";
}

int
chimney_to_suite()
{
	write("You shimmy through the chimney and pop out of the fireplace.\n");
	TP->add_prop(CHIMNEY_INVADER, 1);
	return 0;
}

int
view_roof()
{
	/* This function returns an equivalent of 'look' from trusq_roof
	 * most importantly without any supporting code from the
	 * target room.
	 */

	object *inv, *obs, *ppl, target;
    string desc;

	write(TRUSQ_ROOF->long());
	target = find_object(TRUSQ_ROOF);
	inv = all_inventory(target);
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
	ppl = FILTER_LIVE(inv);

	if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
	write(one_of_list(({"From inside you can make out ",
						"You believe you spot ",
						"Your eyes come across "}))
						+ desc + " atop the roof.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write(one_of_list(({"Outside you see ",
						"You notice below ",
						"Through the shingles you spy "}))
						+ desc + " on the roof.\n");
 
	return 1;
}
