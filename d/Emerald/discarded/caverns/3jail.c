/*
 * 3jail.c
 * This is the main hallway in the jail.
 * - Alaron , September 15, 1996
 */

#include "defs.h"
#include <stdproperties.h>

inherit BASECAVE;

void
create_cave()
{
    set_short("Cavernous hallway");
    set_long("   The foul, rank odor of decay and death assaults "+
	     "your senses as you look around the dimly lit "+
	     "corridor. The dark, damp walls push in on the hallway, "+
	     "creating a tight, enclosed feeling. The hallway leads "+
	     "to the west, revealing a circular chamber containing "+
	     "a large jail cell. You notice that most of the "+
	     "smell of decay is wafting from that direction. The hallway "+
	     "continues in a winding pattern through the dim light "+
	     "to the south.\n\n");

    add_item( ({"cell", "prison cell"}),
	     "You can't quite make out the details of the prison "+
	     "cell from here.\n");
    
    add_item( ({"door", "iron door", "west"}),
	     "You can't quite make out the details of the enormous "+
	     "iron door from here.\n");

    add_item( ({"hallway"}),
	     "The hallway leads west toward a damp, ragged-looking "+
	     "jail cell built into the side of the cavern, and "+
	     "continues to the south.\n");

    add_exit(THIS_DIR + "2jail", "west");
    add_exit(THIS_DIR + "5jail", "south");
}
