/*
 * Corridor
 * Boreaulam, April 2012
 */
#include "defs.h"
#pragma strict_types

inherit L1_BASE_ROOM;
/*
 * Function name:		create_room
 * Description  :		creates room
 */
void
create_room()
{
	::create_room();
    set_short("Cave corridor");
    set_long("You are standing in a bare corridor. " +
             "There is nothing here but walls. " +
             "You can hear noise of weapon clashes from the east. " +
             "\n\n");
    add_item(({"corridor", "bare corridor"}),
             "Little of interest is here other than the unadorned " +
             "surfaces of the walls themselves.\n");
    add_cmd_item( "noise",
                  "listen",
                  "The noise seems like someone fighting. It goes " +
                  "from east part of the corridor.\n");

    add_exit ("roome","west");
    add_exit ("roomg","east");

    add_npc(NPCS_DIR + "goblin1_1", 2, &->arm_me());
} /* create_room */
