#pragma strict_types
/*
 * ~/priv_4.c
 *
 * Private room in Melchior's Bath.
 *
 * Revisions:
 *   Grace,  Feb 1994: Created.
 *   Lilith, Apr 2002: ?
 *   Lucius, Oct 2008: Cleanup.
 *   Lucius, Aug 2016: Recoded baths.
 *
 */
#include "../priv.h"
inherit BATH_PRIV;

static void
create_priv_bath(void)
{
    set_short("Northwest private bath");
    set_long("Surely there are few places in this world which put "+
	"paradise so close to hand as this one! The walls and "+
	"ceiling are of green, epidotic granite left unfinished "+
	"to show the monolithic crystals at their best. The floor "+
	"is laid with polished coppery tiles whose edges echo the "+
	"greenish color of the rock formation from which the room "+
	"is carved. Baskets of rare flowers hang from the flat "+
	"ceiling, erfuming the air with a subtle, tantalizing "+
	"blend of fragrances.  The room is illuminated by a glowing "+
	"crystal whose light is further softened by rising steam. "+
	"Carbonated mineral water, well known for its healing "+
	"properties, flows from a small pool near the ceiling to a "+
	"much larger one which dominates the room. "+
	"There is a sign upon the door.\n");

    add_item(({"flower", "flowers"}),
	"The flowers hang from pots in all sizes and colours.\n");
    add_item(({"wall", "walls", "green rock", "greenish rock",
	"monolithic crystals", "granite", "epidotic granite"}),
	"The room appears to have been carved from a mass of "+
	"epidotic granite composed primarily of large greenish "+
	"crystals that are lustrous and opaque.\n");
    add_item(({"floor", "tile", "tiles", "copper tiles"}),
	"The floor is laid with copper tiles whose edges have a "+
	"greenish patina that complements the green of the walls "+
	"and ceiling.\n");
    add_item(({"light", "crystal"}),
	"Built into the ceiling is a large, faceted chunk of the glowing "+
	"crystal which those native to Sybarus call 'The Source'.\n");

    add_cmd_item(({"wall","walls"}), ({"feel","touch"}),
	"The walls feel smooth and damp to the touch.\n");
    add_cmd_item(({"flower", "flowers"}), ({"pick","get","take"}),
	"How selfish you would be, to pick a flower whose beauty "+
	"will only fade in an hour's time! It is best to leave "+
	"it where it is, that its glory may be appreciated by all.\n");

    bath_door("four", "arc_nw", "se");
}

public void
hook_smelled(string str)
{
    write("The air smells vaguely floral.\n");
}
