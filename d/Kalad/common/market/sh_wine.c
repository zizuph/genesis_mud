inherit "/std/room";

#include "/d/Kalad/defs.h"

void
create_room()
{
   set_short("Inside Wine n' Spirits Shop");
   set_long("Inside Wine n' Spirits Shop.\n");
   
   add_exit(MRKT_PATH(m14), "south");
}
