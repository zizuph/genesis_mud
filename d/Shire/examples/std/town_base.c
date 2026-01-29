/*        town_base.c
 *
 *  This is a base inheritable file for the inside buildings of
 *  of town.  You add everything in which you want to have common
 *  to every room that this file is inherited by.
 */

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

inherit SHIRE_ROOM;

/*  You use create_town_room to create your rooms.  It is the
 *  last thing called from the create_shire_room() and anything
 *  you put within the function will be what's added to the room.
 */
void
create_town_room()
{

}

/* The function create_shire_room creates a room with all the shire
 * room functionality.. no need to create a room using create_room
 * when you inherit /d/Shire/std/room.c in fact you should never
 * use create_room with the Shire/std/room.
 */
public void
create_shire_room()
{
    //  Put in whatever you wish to be in _every_ room that this file inherits
    add_item(({"walls","wall"}),"The walls are rather plain looking "+
	     "with the occasional torch placed along it.\n");
    add_item(({"torch","torches"}),"The torches send off a soft light "+
	     "throughout the room.\n");
    add_item("floor","The floor is so clean you could eat off it!\n");
    add_item("ceiling","High above you is the ceiling.\n");
    
    add_prop(ROOM_I_LIGHT, 2);  // Torches add extra light.
    add_prop(ROOM_I_INSIDE, 1); // This is an indoor room  
    create_town_room();
}
