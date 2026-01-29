inherit "/std/room";

#include "/d/Kalad/defs.h"

void
create_room()
{
   set_short("Inside Clothing Shop");
   set_long("Inside Clothing Shop.\n");
   
   add_exit(MRKT_PATH(m05), "north");
}
