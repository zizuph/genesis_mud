#include "/d/Kalad/defs.h"

inherit MRKT_PATH(marketStd);

void
create_room()
{
   ::create_room();
   
   add_exit(MRKT_PATH(m20), "south");
   add_exit(MRKT_PATH(m23), "east");
   add_exit(MRKT_PATH(m27), "north");
   add_exit(MRKT_PATH(m28), "northwest");
   add_exit(MRKT_PATH(sh_gem), "west");
}
