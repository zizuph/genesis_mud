/* 
 * Highbulp's Room in the Aghar Mines in Krynn Newbie Zone
 * a16.c
 */

#include <macros.h>
#include "../local.h"
#include CLOCKH

inherit PAL_GULLY_BASE;

object dwarf1;
/*
 * Function name: reset_pal_gully_room
 * Description  : Resets the room
 */
void
reset_pal_gully_room()
{
    if (!objectp(dwarf1))
    {
        dwarf1 = clone_object(LIV + "agharhighbulp");
        dwarf1->move(TO);
    }
}

/*
 * Function name: create_pal_gully_room()
 * Description  : Constructor for the room, modify this to change room.
 */
void 
create_pal_gully_room()
{
    set_short("Highbulp's Chamber");
    set_long("This room is filled almost completely with "
    +"garbage and other refuse. It runs from wall to wall "
    +"with only the entrance and a giant garbage throne visible. "
    +"This is the chamber of the Highbulp, leader "
    +"of the Aghar Dwarves.\n");
    
    add_item(({"throne", "giant throne", "chair", "garbage throne",
	"giant garbage throne"}), 
    "This is one of the largest 'chairs' you have ever seen. "
    +"Made entirely from garbage it is a wonder anyone can sit in it.\n");
    
    
    add_exit(RDIR + "a15","northwest",0);
    reset_pal_gully_room();
    
}