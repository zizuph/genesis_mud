/*
 *  faerun/underdark/upper/menzo/melee/first_a3.c
 *
 *   
 *  Training arena, Melee-magthere.
 *  Created by Midnight, 8-4-2004
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
    set_short("Muddy training arena of Melee-magthere");
	set_long("This is a part of the huge training hall of " +
        "Melee-magthere. The ceiling is high above, " +
        "the spacious room is only cut by a bridge " +
        "which runs across the hall on the second floor. " +
        "The floor of this part of the training hall " +
        "is covered with a brownish sticky mud, to provide the " +
        "students with the training of fighting on such a surface.\n ");
        
        add_item(({"ceiling", "up" }),
        "The ceiling is raised high above you, and it's difficult to " +
        "determine just how high, because of the darkness which " +
        "envelops the large training arena.\n"); 
        
         add_item(({"floor","mud" }),
        "The floor is covered with a brownish sticky mud, " +
        "framed by dark wooden planks.\n"); 
        
         add_item(({"bridge" }),
        "A bridge runs across the arena on the second floor, " +
        "it would surely provide a great overview of the arena.\n");
        
       
        add_exit("first_a5","north");
        add_exit("first_a1","south");
        add_exit("first_a4","east");


	set_atmosphere_interval(15);
        add_atmosphere("It feels like the mud is taking a steady grip around your feet.\n");
        reset_room();
}

