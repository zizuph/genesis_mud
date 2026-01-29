/*
 *  faerun/underdark/upper/menzo/melee/first51.c
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
	set_short("At the beginning of a cross-corridor, by the stairs");
	set_long("A stair carved out of black stone is placed " +
                 "in the center of the room, each step is marked by " +
                 "a set of small red rubies, which magically glows " +
                 "in the dark. " +
                 "The floors in the room are swept clean to " +
                 "perfection and a luminous trail of soft crimson red " +
                 "light runs in the middle of the floor, like a trail " +
                 "of blood guiding the way further into the dark " +
                 "corridor. The walls of the corridor is lost in " +
                 "the shadows, but the corridor still feels quite " +
                 "roomy.\n"); 
		 
        add_item(({"stair","stairs"}),
        "A stair carved out of black stone is placed " +
        "in the center of the room, each step is marked by " +
        "a set of small red rubies, which magically glow " +
        "in the dark.\n");
        
        add_item(({"step","steps"}), 
        "Steps has been carved out of black " +
        "stone to form a stair. Each step is marked by " +
        "a set of small red rubies, which magically " +
        "glow in the dark.\n"); 
        
        add_item(({"ruby","rubies"}), 
        "They glow softly in the darkness, as if they are burning " +
        "inside.\n"); 
        
        add_exit("first52", "east");
        add_exit("first2","west");
      

}

