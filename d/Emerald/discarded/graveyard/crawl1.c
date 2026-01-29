inherit "/d/Emerald/std/dir_room";

#include "/d/Emerald/defs.h"
#define WEST GRAVEYARD_DIR + "crawl2"
#define EAST GRAVEYARD_DIR + "ingrave"
#define DP(LABEL) ("@@dir_phrase|" + LABEL + "@@")



void
create_room()
{
   set_short("Tunnel under the graveyard.\n");
   set_long("You are crawling along a narrow tunnel under the " +
      "graveyard. The light from the grave is just visible "+DP("direction")
      +" you. The tunnel is so tight, you don't think you'd be able to "+
      "turn around easily.\n" );
   
   
   add_dir_phrase("direction", EAST, "behind");
   add_dir_phrase("direction", WEST, "ahead of");
   add_dir_phrase("direction", 0, "behind");
   
   
   add_prop(ROOM_I_INSIDE,1);
   
   add_exit(DP("exit"),"forward",0,1);
   
   add_dir_phrase("exit", WEST, EAST);
   add_dir_phrase("exit", EAST, WEST);
   add_dir_phrase("exit", 0, WEST);
}
