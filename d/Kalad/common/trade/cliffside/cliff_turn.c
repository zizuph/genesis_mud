inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void
create_room()
{
   set_short("Corner of Cliffside Road and Wall Street");
   set_long("Cliffside Road comes to an end here, and Wall Street begins. "
      +"Southeast of you is the entrance to a tower, "
      +"which guards can be seen to come into and out of. "
      +"Wall street goes far to the north into the caravan district "
      +"of Kabal.\n");
   add_exit(TRADE(cliffside/cliffside1),"west");
   add_exit(TRADE(wall/wall1),"north");
   add_exit(TRADE(wall/tower1),"southeast");
   add_item(({"tower"}),"The tower is large and stone and the typical "
      +"guard tower of the city. It has stone walls and "
      +"rises three stories into the sky.\n");
   hear_bell = 1;
}
