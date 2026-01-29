/*
 *  faerun/underdark/upper/menzo/melee/first48.c
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
	set_short("In a shadowy small training room");
	set_long("This is a shadowy small training room, where students " +
                 "can practice alone, in pairs or together with " +
                 "a master. The stone walls are cut in a perfect " +
                 "circle, designed to keep a battle going " +
                 "so no one gets cornered. A rounded opening leads " +
                 "out to a dark corridor.\n");


        add_exit("first47", "west");
        reset_room();
}