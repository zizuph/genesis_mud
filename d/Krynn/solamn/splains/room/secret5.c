/* created by Aridor 01/05/94 */

#include "../local.h"

inherit INSIDE_BASE;

#define VKEEPLEDGE "/d/Krynn/solamn/vin/room/ledge"

void
create_splains_room()
{
   set_short("In a duct");
   set_long("You are in a narrow chamber, there is a ladder going " +
      "down and a light to your north.\n");
   DARK;
   add_exit(ROOM + "secret4","down");
   add_exit(VKEEPLEDGE, "out", "@@fall_in_the_room");
}

int
fall_in_the_room()
{
   write("You pop out of the tunnel and find yourself starting at "+
      "the moat around Vingaard about three inches below your nose. "+
      "You scurry out of the tunnel and pull yourself up on a small "+
      "ledge at the base of the wall.\n");
   return 0;
}
