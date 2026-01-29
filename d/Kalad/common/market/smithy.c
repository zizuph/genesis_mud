inherit "/std/room";

#include "/d/Kalad/defs.h"

void
create_room()
{
   set_short("Inside Armoury.\n");
   set_long("Inside Armoury");
   
   add_exit(MRKT_PATH(m03), "east");
}
