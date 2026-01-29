/* 	this is a room of the town Gelan

    coder(s):   Merlin, Maniac & Deinonychus

    history:
                15.9.95     description amended             Maniac
                28.09.94    add_square_items inserted       Deinonychus
                21.09.94    SQUARE_ROOM replaces /std/room  Deinonychus
                21. 2.93    path system                     Merlin
                 2.02.93    descriptions	            Deinonychus
	         3.11.92    created                         Merlin
                 6.11.92    installed help system           Merlin
                 7.11.92    corrected false exit            Merlin

    purpose:    square
    exits:      all to square

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

  set_short("Square west");

  set_long("From this west point in the town square you get a distant view "
         + "of all the buildings that you will find on the west side. "
         + "To your north you see the post office, south is the grocery, "
         + "southwest are the smithy and bank, and northwest you see the "
         + "shop and the alchemist's house. To the east the "
         + "square stretches out, with a fountain at its centre, and "
         + "a long way to the southeast you can just see the town gate.\n");
  
  /* properties */

  add_prop(ROOM_I_INSIDE, 0);	/* this room is outside */

  add_item(({"post office", "grocery", "smithy", "bank", "gate",
             "shop", "alchemist", "alchemist's house"}),
           "You'll need to go closer to get a proper look.\n");

  /* exits */

  add_exit(GELAN_ROOMS + "square_wn","north",0);
  add_exit(GELAN_ROOMS + "square_fountain_w","south",0);
  add_exit(GELAN_ROOMS + "square_westend","west",0);
  add_exit(GELAN_ROOMS + "square_fountain_nw","east",0);
  add_exit(GELAN_ROOMS + "square_westend_n","northwest",0);
  add_exit(GELAN_ROOMS + "square_midw","northeast",0);
  add_exit(GELAN_ROOMS + "square_westend_s","southwest",0);


} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */