/* 
 * Block Room of the Aghar Caverns
 */

#include <macros.h>
#include "../local.h"
#include CLOCKH

inherit PAL_GULLY_BASE; 

/*
 * Function name: reset_pal_gully_room
 * Description  : Resets the room
 */
void
reset_pal_gully_room()
{
	
}

/*
 * Function name: create_pal_gully_room()
 * Description  : Constructor for the room, modify this to change room.
 */
void 
create_pal_gully_room()
{
    set_short("Dimly lit mine");
    set_long("The home of the Aghar Dwarves. The walls of "
        + "the room are roughly hewn by rudimentary "
        + "tools. A large pile of refuse in this room emanates "
        + "a stench beyond description. There is little "
        + "else in this room but garbage and filth.\n");

    add_item(({"refuse", "pile", "refuse pile"}), 
	"A large pile of refuse has been stacked in front of the western exit. "
	+"There is a small hole in the refuse pile that may allow you to pass "
    + "west, if you can fit.\n");
	
    
    add_exit(RDIR + "a2","west");
    add_exit(RDIR + "aentrance","north",0);
    
    reset_pal_gully_room();
}

