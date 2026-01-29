inherit "/std/room";

#include "/d/Kalad/defs.h"

void
create_room()
{
   set_short("Underneath a wagon");
   set_long(BS("You are crawling in the mud beneath a rickity, "+
         "old wagon.\n"));
   
   add_exit(MRKT_PATH(m15), "southwest");
   add_exit(MRKT_PATH(m19), "northeast");
}
