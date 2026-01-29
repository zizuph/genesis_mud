inherit MRKT_PATH(marketStd);

#include "/d/Kalad/defs.h"

void
create_room()
{
   ::create_room();
   
   add_exit(MRKT_PATH(m23), "southeast");
   add_exit(MRKT_PATH(m24), "south");
   add_exit(MRKT_PATH(m28), "west");
}
