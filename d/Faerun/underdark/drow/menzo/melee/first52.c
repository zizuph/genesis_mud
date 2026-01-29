/*
 *  faerun/underdark/upper/menzo/melee/first52.c
 *
 *
 *  Corridor on the first floor in the Melee-magthere.
 *  Created by Midnight, 7-4-2004
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
inherit ROOM_IN_BASE;

/*
 * Function name: create_menzo_in_room
 * Description  : Construct a room for the Melee-magthere
 */
void create_menzo_in_room()
{
	set_short("In a dark cross-corridor");
	set_long("This is a dark corridor which runs straight through " +
	         "the first floor. To the east you can see that the " +
	         "corridor opens up into a very spacious hall. The " +
	         "contours of a dark stair can be seen just to the west. " +
	         "The floors in the room are swept clean to " +
                 "perfection and a luminous trail of soft crimson red " +
                 "light runs in the middle of the floor, like a trail " +
                 "of blood guiding the way further into the dark " +
                 "corridor. The walls of the corridor is lost in " +
                 "the shadows, but the corridor still feels quite " +
                 "roomy.\n");


        add_item(({"hall"}),
        "You can see a hall to the east, it looks like it is some " +
        "sort of training arena.\n");

        add_item(({"stair"}),
        "Through the darkness, you can just barely see a stair " +
        "west of here.\n");

        add_exit("first_a1", "east");
        add_exit("first51","west");
        reset_room();
}

