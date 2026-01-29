inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   add_prop(ROOM_I_LIGHT,0);
   set_short("The spider room");
   set_long("A black, featureless void.\n");
}
