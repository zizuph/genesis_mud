/* 
 * Room in the Aghar Mines in Krynn Newbie Zone
 * a2.c
 */

#include <macros.h>
#include "../local.h"
#include CLOCKH

inherit PAL_GULLY_BASE;

object dwarf1;
object dwarf2;
object dwarf3;

/*
 * Function name: reset_pal_gully_room
 * Description  : Resets the room
 */
void
reset_pal_gully_room()
{
    if (!objectp(dwarf1))
    {
        dwarf1 = clone_object(LIV + "aghar");
        dwarf1->move(TO);
    }
    if (!objectp(dwarf2))
    {
        dwarf2 = clone_object(LIV + "aghar");
        dwarf2->move(TO);
    }
	if (!objectp(dwarf3))
    {
        dwarf3 = clone_object(LIV + "aghar");
        dwarf3->move(TO);
    }
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

    add_exit(RDIR + "a3","west",0);
    add_exit(RDIR + "a1","east",0);
    reset_pal_gully_room();
    
}