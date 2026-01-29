inherit "/std/room";

#include "/d/Kalad/defs.h"

void
create_room()
{
   set_short("Inside Gorged Unicorn");
   set_long("Inside Gorged Unicorn.\n");
   
   add_exit(MRKT_PATH(dine01),"north");
}
