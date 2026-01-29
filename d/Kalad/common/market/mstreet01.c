inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"

void
create_room()
{
   ::create_room();
   
   set_short("Market Street");
   set_long("On Market Street.\n");
   
   add_exit(MRKT_PATH(m03), "north");
}
