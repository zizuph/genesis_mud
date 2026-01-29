/*	This is a room of the town Gelan
	
	coder(s):   Merlin, Maniac & Deinonychus
	
        15.9.95     description amended             Maniac      
	20. 2.93    path system                     Merlin
	02.02.93    descriptions	            Deinonychus
	03.11.92    created                         Merlin
	06.11.92    installed help system           Merlin
	
	purpose:    square
	exits:      all except sw to square
	
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

  set_short("Square east");
  set_long("From this east point in the town square you get a distant view "
         + "of all the buildings that you will find on the east side. " 
         + "To your north you see the jail, south is the bakery, southeast " 
         + "are the lavatory and hairdresser, and northeast you see the "
         + "school and the house of a prominent citizen. To the west the "
         + "square stretches out, with a fountain at its centre, and " 
         + "a long way to the southwest you can just see the town gate.\n");
  
  /* properties */

  add_prop(ROOM_I_INSIDE, 0);	/* this room is outside */

  /* exits */


  add_item(({"lavatory", "jail", "bakery", "hairdresser", "gate", 
             "house", "school"}),
           "You'll need to go closer to get a proper look.\n"); 


  add_exit(GELAN_ROOMS + "square_en","north",0);
  add_exit(GELAN_ROOMS + "square_fountain_e","south",0);
  add_exit(GELAN_ROOMS + "square_fountain_ne","west",0);
  add_exit(GELAN_ROOMS + "square_eastend","east",0);
  add_exit(GELAN_ROOMS + "square_mide","northwest",0);
  add_exit(GELAN_ROOMS + "square_eastend_n","northeast",0);
  add_exit(GELAN_ROOMS + "square_eastend_s","southeast",0);

  /* items in the room */

} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */