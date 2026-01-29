/*
 *  faerun/underdark/upper/menzo/melee/first29.c
 *
 *
 *  Corridor on the first floor in the Melee-magthere.
 *  Created by Midnight, 4-4-2004
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
	set_short("A dark eastern corridor on the first floor");
	set_long("You stand in a corridor in the " +
                 "the Melee-magthere of Menzoberranzan. " +
                 "The floors are swept clean to perfection " +
                 "and a luminous trail of soft crimson red " +
                 "light runs in the middle of the floor, like a " +
                 "trail of blood guiding the way further into " +
                 "the dark corridor. The walls of the corridor " +
                 "are lost in the shadows, but the corridor " +
                 "still feels quite roomy. \n");


        add_exit("first30", "west");
        add_exit("first31", "south");
        add_exit("first27", "north");
}