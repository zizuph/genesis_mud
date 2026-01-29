/* 	this is a room of the town Gelan

    coder(s):   Merlin, Maniac & Deinonychus

                 15.9.95    description amended             Maniac 
                 20.2.93    path system                     Merlin
                 2.02.93    descriptions	            Deinonychus
	         3.11.92    created                         Merlin
                 6.11.92    installed help system           Merlin

    purpose:    square
    exits:      south and east to fountain, ne-n-nw-w-sw to quare

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
#include <stdproperties.h>

create_room()
{
  create_square_room();
  
  /* descriptions */
  
  set_short("Square fountain northwest");
  set_long("You're standing northwest of the fountain that marks the centre "
        + "of the town square of Gelan. All around you the square stretches "
        + "out, with colourful buildings of various shapes and sizes "
        + "on every side. A fair way to the northeast you see the pillory, "
        + "while a long way to the south are the palace road and gate.\n");
  
  /* properties */
  
  add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */
  

   add_item(({"pillory", "gate", "palace road"}), 
              "You'll need to go closer to get a proper look.\n"); 
  /* exits */
  
  add_exit(GELAN_ROOMS + "square_midw","north",0);
  add_exit(GELAN_ROOMS + "fountain_w","south",0);
  add_exit(GELAN_ROOMS + "square_w","west",0);
  add_exit(GELAN_ROOMS + "fountain_northend_w","east",0);
  add_exit(GELAN_ROOMS + "square_wn","northwest",0);
  add_exit(GELAN_ROOMS + "square_central_w","northeast",0);
  add_exit(GELAN_ROOMS + "square_fountain_w","southwest",0);
  
  /* items in the room */
  
} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */