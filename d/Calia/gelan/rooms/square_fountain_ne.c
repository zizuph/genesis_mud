/* 	this is a room of the town Gelan

    coder(s):   Merlin, Maniac & Deinonychus

                 15.9.95    description amended             Maniac
                  7.9.94    privisional descr added         Maniac 
                20. 2.93    path system                     Merlin
                17. 1.93    new guard system                Merlin
                 9. 1.93    townrooms.h -> room.h           Merlin
                 6.11.92    installed help system           Merlin
                 3.11.92    created                         Merlin

    purpose:    square
    exits:      south and east to fountain, se-e-ne-n-nw to square

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
  
  set_short("Square fountain north east");
  set_long("You're standing northeast of the fountain that marks the centre "
        + "of the town square of Gelan. All around you the square stretches "
        + "out, with colourful buildings of various shapes and sizes "
        + "on every side. A fair way to the northwest you see the pillory, "
        + "while a long way to the south are the palace road and gate.\n");
  
  /* properties */
  
  add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */
  
  add_item(({"pillory", "gate", "palace road"}),
             "You'll need to go closer to get a proper look.\n");


  /* exits */
  
  add_exit(GELAN_ROOMS + "square_mide","north",0);
  add_exit(GELAN_ROOMS + "fountain_e","south",0);
  add_exit(GELAN_ROOMS + "fountain_northend_e","west",0);
  add_exit(GELAN_ROOMS + "square_e","east",0);
  add_exit(GELAN_ROOMS + "square_central_e","northwest",0);
  add_exit(GELAN_ROOMS + "square_en","northeast",0);
  add_exit(GELAN_ROOMS + "square_fountain_e","southeast",0);
  
  /* items in the room */
  
} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */