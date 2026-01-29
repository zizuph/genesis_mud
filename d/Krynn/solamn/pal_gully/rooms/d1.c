/* 
 * First Room of the Dewar Caverns
 * d1.c
 */

#include <macros.h>
#include "../local.h"
#include CLOCKH

inherit PAL_DEWAR_BASE; 

/*
 * Function name: reset_pal_dewar_room
 * Description  : Resets the room
 */
void
reset_pal_dewar_room()
{
	
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
    +"carved. This room is large and set up as a guard "
    +"post. Small desks sit along the edge of "
    +"the room and there is a barricade here for "
    +"some reason. Cursing echoes throughout the caverns "
    +"and the blood stains on the floor point to nefarious activities.\n");
        
    add_item(({"desk", "desks","edge", "edge of room"}),
	"Small wooden desks which have been built "
    +"hastily and seem to be poorly put together.\n");
    add_item(({"barricade"}), "A crude barricade that honestly wouldn't "
    +"stop anyone from passing.\n");	
       
    add_exit(RDIR + "d2","west",0);
    add_exit(RDIR + "dentrance","south",0);
    
    reset_pal_dewar_room();
    
}