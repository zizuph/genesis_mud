/*
 *  faerun/underdark/upper/menzo/melee/first_a8.c
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
	set_short("Training arena with poles of Melee-magthere");
	set_long("This is a part of the huge training hall of " +
        "Melee-magthere. The ceiling is high above, " +
        "the spacious room is only cut by a bridge " +
        "which runs across the hall on the second floor. " +
        "The floor of this part of the training hall " +
        "is constructed of widely separated balancing poles, " +
        "to provide the students with the training of fighting " +
        "in such an environment.\n ");
        
       
    add_exit("first_a7","north");
    add_exit("first_a10","east");

    set_atmosphere_interval(15);
    add_atmosphere("You struggle to keep your balance on one of the poles.\n");
        reset_room();
}

