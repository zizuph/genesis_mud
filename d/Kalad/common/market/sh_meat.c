inherit "/std/room";

#include "/d/Kalad/defs.h"

void
create_room()
{
   set_short("Inside Meats and Beef Shop");
   set_long("Inside Meats and Beef Shop.\n");
   
   add_exit(MRKT_PATH(m14), "west");
}
