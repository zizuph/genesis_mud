/* A room near the wall in the fountain in Gelan.

   Originally coded by Snarf (?)
   Some corrections made by Maniac 7.94 
   Typos taken out by Maniac 14/7/95
*/
   

#include "room.h"
#pragma save_binary

inherit GELAN_ROOMS + "fwroom";
#include <stdproperties.h>
#include <macros.h>
#include GUARD_INCLUDE
 
void
create_water_room()
{
  make_fountain_wall(); 
  set_short("Fountain northend west");
  set_long("You are standing in the northern part of the fountain where " +
       "the deep blue sparkling water, gushing forward from the " +
       "fountain's centre, reaches up to your knees. " +
       "The fountain is surrounded by a one foot high stone wall. " +
       "To the southeast, in the middle of the fountain, a mighty " +
       "golden statue of Caliana fighting a black dragon rises into " +
       "the sky. Further away you see the city square expanding in " +
       "all directions.\n");
  
  add_prop(ROOM_I_INSIDE, 0);
  add_prop(ROOM_I_TYPE,   ROOM_IN_WATER);
  
  add_exit(GELAN_ROOMS + "square_central_w","north",0);
  add_exit(GELAN_ROOMS + "fountain_statue_w","south",0);
  add_exit(GELAN_ROOMS + "square_fountain_nw","west",0);
  add_exit(GELAN_ROOMS + "fountain_northend_e","east",0);
  add_exit(GELAN_ROOMS + "fountain_w","southwest",0);
  add_exit(GELAN_ROOMS + "fountain_statue_e","southeast",0);
}
