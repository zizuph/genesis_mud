#include "/d/Kalad/defs.h"

inherit MRKT_PATH(marketStd);

void
create_room()
{
   ::create_room();
   
   add_exit(MRKT_PATH(m21), "east");
   add_exit(MRKT_PATH(m26), "north");
   add_exit(MRKT_PATH(m23), "west");
}
