#include "/d/Kalad/defs.h"

inherit "/std/room";

void
create_room()
{
   
   set_short("Inside Gems n' Jewelry");
   set_long("Inside Gems n' Jewelry.\n");
   
   add_exit(MRKT_PATH(m24), "east");
}
