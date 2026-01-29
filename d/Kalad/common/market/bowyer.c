inherit "/std/room";

#include "/d/Kalad/defs.h"

void
create_room()
{
   set_short("Inside Bowyer's Shop");
   set_long("Inside Bowyer's Shop.\n");
   
   add_exit(MRKT_PATH(m17), "south");
}
