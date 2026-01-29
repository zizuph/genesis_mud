/* this is a room of the town Gelan
    
   coder(s):   Merlin, Maniac & Deinonychus
   
   history:
   15.9.95     description amended             Maniac    
   ??.08.94    typos removed                   Maniac 
   20.02.93    path system                     Merlin
   02.02.93    descriptions		       Deinonychus
   03.11.92    created                         Merlin
   06.11.92    installed help system           Merlin
   
   purpose:    square
   exits:      east to road east, n-nw-w-sw-s to square
   
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
  
  set_short("Square east end");
  set_long("You're standing at the east end of the town square of Gelan. "
         + "The town school may be reached by proceeding "
         + "north then east, while going south then east will take you "
         + "to the hairdresser, a house in the shape of a shampoo bottle. "
         + "To your west the town square opens out, surrounded by a colourful "
         + "array of buildings. The beautiful fountain at the centre of the "
         + "square is some way to your west, while Maple street lies to " 
         + "your east.\n");

  /* properties */
  
  add_prop(ROOM_I_INSIDE, 0);	  /* this room is outside */
  
  /* exits */
  
  add_exit(GELAN_ROOMS + "square_eastend_n","north",0);
  add_exit(GELAN_ROOMS + "square_eastend_s","south",0);
  add_exit(GELAN_ROOMS + "square_e","west",0);
  add_exit(GELAN_ROOMS + "road_e","east",0);
  add_exit(GELAN_ROOMS + "square_en","northwest",0);
  add_exit(GELAN_ROOMS + "square_fountain_e","southwest",0);
  
  /* items in the room */
  
  add_square_items("school");
  add_square_items("hairdresser");
} /* create_room */
