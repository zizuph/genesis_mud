inherit "/std/room";

#include "/d/Kalad/defs.h"

void
create_room()
{
   
   set_short("Inside Hakim's Herb and Spice Shop");
   set_long("Inside Hakim's Herb and Spice Shop.\n");
   
   add_exit(MRKT_PATH(m18), "southeast");
}
