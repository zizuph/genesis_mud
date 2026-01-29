/*
 *  faerun/underdark/upper/menzo/melee/first_a9.c
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
	set_short("Training arena with a basin of Melee-magthere");
	set_long("This is a part of the huge training hall of " +
        "Melee-magthere. The ceiling is high above, " +
        "the spacious room is only cut by a bridge " +
        "which runs across the hall on the second floor. " +
        "The floor of this part of the training hall " +
        "is a basin of knee-deep water, to provide the " +
        "students with the training of fighting on such a surface.\n ");
       
        add_exit("first_a2","north");
        add_exit("first_a10","south");
        add_exit("first_a7","west");


	set_atmosphere_interval(15);
        add_atmosphere("The dark waters around you slows your movement.\n");
        reset_room();
}

