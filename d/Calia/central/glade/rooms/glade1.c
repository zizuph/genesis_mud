//ROOM: Triel glade 1

/*  Calia Domain
 *
 *  HISTORY:
 *
 *    [99-01-02] Created by Sheytansha
 *
 *  PURPOSE:
 *
 *  This is the first of 10 rooms located in the Great triel Forest.
 *  The main idea behind the glade was just a small area where players
 *  could come and relax. Perhaps at a future point in time, a quest
 *  could also be incorporated using this area. The map is as follows:
 *
 * 		      4  7* 6		8*--9
 *			|  | /|
 *     		|  |10|	(The "*" indicates a room where climbing
 *			3--2--5	 is necessary to reach the ledge from which
 *			   |		 a player can dive from into the room below.)
 *			   1
 */

    
// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include "defs.h"

// ROOM DEFINITION

void
create_room()
{

    set_short("triel glade");
    set_long("You stand in a serene glade, the sound of running" +
        " water gurgles quietly all around you. Beams of sunlight" +
        " filter through the canopy of the trees looming above you." +
        " The area is thick with vegatation, making it feel rather" +
        " muggy. To your north you see a neatly groomed path of grey" +
        " shale leading you further into the glade; to the south is" +
	  " the underbrush from which you crawled through.\n");

    add_item(({"glade"}), "Dozens of colourful plants surround you, making" +
        " this a pleasurable retreat for the senses.\n");
    add_item(({"plants", "vegetation"}), "
    add_item(({"trees"}), " \n");

    add_exit(GLADE_ROOMS + "glade2", "north", 0);
 
}

