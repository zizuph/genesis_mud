/* 
 * Second Room of the Dewar Caverns
 * d2.c
 */


#include <macros.h>
#include "../local.h"
#include CLOCKH

inherit PAL_DEWAR_BASE; 

object dwarf1;
object dwarf2;
object dwarf3;

/*
 * Function name: reset_pal_dewar_room
 * Description  : Resets the room
 */
void
reset_pal_dewar_room()
{
    if (!objectp(dwarf1))
    {
        dwarf1 = clone_object(LIV + "dewar");
        dwarf1->move(TO);
    }
    if (!objectp(dwarf2))
    {
        dwarf2 = clone_object(LIV + "dewar");
        dwarf2->move(TO);
    }
	if (!objectp(dwarf3))
    {
        dwarf3 = clone_object(LIV + "dewar");
        dwarf3->move(TO);
    }
}

/*
 * Function name: create_pal_dewar_room()
 * Description  : Constructor for the room, modify this to change room.
 */
void 
create_pal_dewar_room()
{
    set_short("Well-Lit Cavern System");
    set_long("The home of the Dewar Dwarves. "
    +"The walls of the caverns are smooth and well "
    +"carved. This room is large and set up as a "
    +"guard post. On the other side of the barricade now, "
    +"small desks sit along the edge of the room for "
    +"the Dewar guards. Cursing echoes throughout the caverns "
    +"and the blood stains on the floor point to "
    +"nefarious activities. This room is lit by oil lanterns "
    +"attached to the walls.\n");
    
    add_item(({"desk", "desks","edge", "edge of room"}),
	"Small wooden desks which have been built "
    +"hastily and seem to be poorly put together.\n");
    add_item(({"barricade"}), "A crude barricade that honestly wouldn't "
    +"stop anyone from passing.\n");	
	
    add_exit(RDIR + "d3","west",0);
    add_exit(RDIR + "d1","east",0);
    reset_pal_dewar_room();
    
}