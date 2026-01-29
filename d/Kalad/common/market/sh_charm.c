#include "/d/Kalad/defs.h"

inherit "/std/room";

void
create_room()
{
   
   set_short("Inside Talisman Shop");
   set_long("Inside Talisman Shop.\n");
   
   add_exit(MRKT_PATH(m15), "north");
}
