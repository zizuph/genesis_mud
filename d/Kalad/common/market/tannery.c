inherit "/std/room";

#include "/d/Kalad/defs.h"

void
create_room()
{
   set_short("Inside Tannery");
   set_long("Inside Tannery.\n");
   
   add_exit(MRKT_PATH(m09), "north");
}
