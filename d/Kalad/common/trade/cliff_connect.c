inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"
object thief;

void
create_room()
{
   set_short("A dark alley");
   set_long("You have entered a dark alley. All around there lies trash "
      +"and other rubbish. You are surprised that no thieves have "
      +"attacked you yet.\n");
   add_exit(TRADE(cc1),"south");
   add_exit(TRADE(cliff_connect2),"north");
   add_item(({"trash","rubbish"}),"This is just garbage, nothing interesting.\n");
   hear_bell = 1;
   thief = clone_object("/d/Kalad/common/trade/thief.c");
   thief-> move_living("xxx",TO);
}
