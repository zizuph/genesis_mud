inherit MRKT_PATH(marketStd);

#include "/d/Kalad/defs.h"

void
create_room()
{
   ::create_room();
   
   add_exit(MRKT_PATH(blower), "west");
   add_exit(MRKT_PATH(stall02), "east");
   add_exit(MRKT_PATH(m22), "south");
}
