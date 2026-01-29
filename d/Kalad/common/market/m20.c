#include "/d/Kalad/defs.h"

inherit MRKT_PATH(marketStd);

void
create_room()
{
   ::create_room();
   
   add_exit(MRKT_PATH(m16), "south");
   add_exit(MRKT_PATH(m17), "southwest");
   add_exit(MRKT_PATH(m23), "northeast");
   add_exit(MRKT_PATH(m24), "north");
}
