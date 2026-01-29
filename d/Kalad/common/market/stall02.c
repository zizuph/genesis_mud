inherit "/std/room";

#include "/d/Kalad/defs.h"

void
create_room()
{
   set_short("Inside an empty stall");
   set_long("Inside an empty stall.\n");
   
   add_exit(MRKT_PATH(m26), "west");
}
