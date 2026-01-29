inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   hear_bell = 1;
   INSIDE;
   set_short("The private office of the Guildmaster");
   set_long("You are within the private office of the Guildmaster of the "+
      "Merchants Guild of Kabal.\n");
   add_exit(CVAN(guild/meeting),"down",0,-1,-1);
}
