/* 
 * Mortis 03.2006
 *
 * Ground floor chimney vent of merchant house Trusq.
 *
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>

#define TRUSQ_HALL				SHIP + "trusq_hall"
#define FOUND_FIREPLACE_HOLE	"_i_found_trusq_fireplace_hole"

inherit SHIP_ROOMBASE;

void
reset_palan_room()
{
}

void
create_palan_room()
{
    SHORT("In a wide brick chimney above a fireplace");
    LONG("Oily soot coats the bricks inside this cramped chimney.  Down "
	+ "below is a fireplace that opens onto a large hall.  Above you, a "
	+ "metal grate blocks the chimney.\n");

	ITEM("hall", "The hall is through the fireplace from here.\n");
	ITEM("chimney", "You are in the chimney.  Have a <look> around?\n");
	ITEM(({"fire", "fireplace"}), "A brick fireplace is below you."
	+ "@@exa_fire@@" + "\n");
	ITEM(({"ash", "ashes"}), "Ashes from spent fires lay scattered in the "
	+ "fireplace below.\n");
	ITEM("vent", "@@exa_vent");
	ITEM("grate", "A metal grate prevents you from climbing higher through "
	+ "the chimney but allows for smoke to rise.  You find no weakness in "
	+ "its protection, not even its sooty screws.\n");
	ITEM(({"screw", "screws"}), "Heavy, soot covered screws keep the metal "
	+ "grate in place.  They are too tight and strong to budge.\n");
	ITEM("soot", "Thick, oily soot coats the bricks inside this cramped "
	+ "chimney.  It's getting all over you.\n");
	ITEM(({"brick", "bricks"}), "The bricks are completely coated in oily "
	+ "soot.\n");

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

	EXIT(SHIP + "trusq_hall", "down", 0, 0);

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
