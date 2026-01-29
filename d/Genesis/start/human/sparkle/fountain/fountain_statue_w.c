/* A room near to the statue in the fountain in Gelan.

   Originally coded by Snarf (?)
   Some corrections made by Maniac 7.94 
   Typos corrected by Maniac 14/7/95
*/
   

#include "room.h"
#include <stdproperties.h>
#include <macros.h>
#include GUARD_INCLUDE

/* Presumably in this room you aren't near enough to the walls to see so 
   don't inherit "fwroom" */

#pragma save_binary

inherit GELAN_ROOMS + "fountain";
 
void
create_water_room()
{
  make_fountain();
 
  set_short("Fountain statue west");
  set_long("You are standing in the middle of the fountain where " +
           "the deep blue sparkling water, gushing forward from the " +
           "fountain's centre, reaches up to your waist. " +
           "Immediately to the east, in the middle of the fountain, a " +
           "mighty golden statue of Caliana fighting a black dragon rises " +
           "into the sky. Further away, beyond the fountain, you see the " +
           "city square expanding in all directions.\n");
  
  add_prop(ROOM_I_INSIDE, 0);
  add_prop(ROOM_I_TYPE,   ROOM_IN_WATER);
 
  add_exit(GELAN_ROOMS + "fountain_northend_w","north",0);
  add_exit(GELAN_ROOMS + "fountain_southend_w","south",0);
  add_exit(GELAN_ROOMS + "fountain_w","west",0);
  add_exit(GELAN_ROOMS + "fountain_statue_e","east",0);
  add_exit(GELAN_ROOMS + "fountain_northend_e","northeast",0);
  add_exit(GELAN_ROOMS + "fountain_southend_e","southeast",0);
}
