
/* 
    this is a room of the town Gelan

    coder(s):   Merlin

    history:    
                 12/4/98     gopheroo resets here            Maniac
                 28/5/96     updated                         Maniac
                 17.09.94    SQUARE_ROOM replaces /std/room  Deinonychus
                 20. 2.93    path system                     Merlin
                  2.02.93    descriptions		     Deinonychus
                  6.11.92    installed help system           Merlin
		  3.11.92    created                         Merlin

    purpose:    square
    exits:      w-e-ne-se to sqaure, n-nw to pillory, s to fountain

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


#include "room.h"
#pragma save_binary

inherit SQUARE_ROOM;
#include GUARD_INCLUDE
#include <stdproperties.h>
#include <macros.h>


object gopheroo; 


void
gopheroo_bolt()
{
    gopheroo->bolt(); 
}


void
reset_room()
{
    if (!objectp(gopheroo)) {
        gopheroo = clone_object(GELAN_MONSTERS + "gopheroo"); 
        gopheroo->move_living("X", this_object()); 
        set_alarm(1.0, 0.0, gopheroo_bolt); 
    }   
}


void
remove_object()
{
    gopheroo->remove_object(); 
    ::remove_object(); 
}


void
create_room()
{
    create_square_room();
    set_short("Square central east");
    set_long("You're at a central point in the town square. To your " +
	"north you see the famous pillory of Gelan, while southwards is " +
	"the beautiful fountain. All around the square you see " +
	"interesting buildings.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "pillory_e","north",0);
    add_exit(GELAN_ROOMS + "fountain_northend_e","south",0);
    add_exit(GELAN_ROOMS + "square_central_w","west",0);
    add_exit(GELAN_ROOMS + "square_mide","east",0);
    add_exit(GELAN_ROOMS + "pillory_w","northwest",0);
    add_exit(GELAN_ROOMS + "square_ne","northeast",0);
    add_exit(GELAN_ROOMS + "square_fountain_ne","southeast",0);

    /* items in the room */

    add_item("pillory", DESC("pillory"));

    reset_room(); 
} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
