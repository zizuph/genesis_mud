inherit "/std/room";
#include "/d/Kalad/defs.h"
void
create_room()
{
    set_short("\n" + "Inside Money Changer's Shop\n\n");
    set_long("\n"+
      "You are standing inside the Market District's "+
      "Money Changer's Shop. "+
      "\n\n");
    add_exit(MRKT_PATH(m12), "north");
}
