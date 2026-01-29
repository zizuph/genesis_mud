/* 	this is a room of the town Gelan

    coder(s):   Merlin, Deinonychus & Maniac

    history:
                15.9.95     description amended             Maniac
                28.09.94    add_square_items inserted       Deinonychus
                21.09.94    SQUARE_ROOM replaces /std/room  Deinonychus
                    9.94    typos taken out                 Maniac
                21. 2.93    path system                     Merlin
                 2.02.93    descriptions	  	    Deinonychus
	         3.11.92    created                         Merlin
                 6.11.92    installed help system           Merlin

    purpose:    square
    exits:      west to road west

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

  set_short("Square west end");
  set_long("You're standing at the west end of the town square of Gelan. "
         + "The posh local shop may be reached by proceeding " 
         + "north then west, while going south then west will take you "
         + "to the bank, a cube-shaped building made of sandstone. To your "
         + "east the town square opens out, surrounded by a colourful "
         + "array of buildings. The beautiful fountain at the centre of the " 
         + "square is some way to your east, while Surgery street lies to " 
         + "your west.\n");
  
  /* properties */
  
  add_prop(ROOM_I_INSIDE, 0);	/* this room is outside */

  /* exits */

  add_exit(GELAN_ROOMS + "square_westend_n","north",0);
  add_exit(GELAN_ROOMS + "square_westend_s","south",0);
  add_exit(GELAN_ROOMS + "road_w","west",0);
  add_exit(GELAN_ROOMS + "square_w","east",0);
  add_exit(GELAN_ROOMS + "square_wn","northeast",0);
  add_exit(GELAN_ROOMS + "square_fountain_w","southeast",0);

  /* items in the room */

  add_square_items("shop");
  add_square_items("bank");

} /* create_room */
