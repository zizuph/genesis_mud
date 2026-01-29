inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   hear_bell = 1;
   set_short("Store room");
   set_long("You are in the store room of Anthios' general store.\n");
   add_exit(CVAN(guild/shop),"east",0,-1,-1);
}
