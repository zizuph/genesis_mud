#include "/d/Kalad/defs.h"

inherit MRKT_PATH(marketStd);

void
create_room ()
{
   ::create_room();
   
   set_short("A street in the market");
   set_long("This is a street much like any other "+
        "in the crowded noisy market. Only to the north "+
       "you notice a sinister black tower of the sort usually "+
        "inhabited by wizards. You definately feel that "+
        "going there would be a very bad idea indeed!\n");
   add_exit(MRKT_PATH(m19), "south");
   add_exit(MRKT_PATH(m25), "northeast");
   add_exit(MRKT_PATH(m22), "west");
   add_exit("/d/Kalad/cyric/workroom","north");
}
