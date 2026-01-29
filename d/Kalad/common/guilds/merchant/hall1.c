inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   hear_bell = 1;
   INSIDE;
   set_short("Hallway within the Merchants Guild");
   set_long("A narrow hallway within the Merchants Guild of Kabal.\n");
   add_exit(CVAN(guild/bank),"west",0,-1,-1);
   add_exit(CVAN(guild/joinroom),"north",0,-1,-1);
   add_exit(CVAN(guild/shop),"east",0,-1,-1);
   add_exit(CVAN(guild/hall2),"south",0,-1,-1);
}
