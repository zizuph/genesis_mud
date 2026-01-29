/* File: /d/Shire/common/trollsh/rivend2.c */

#include "defs.h"
inherit STAND_EROAD;

object troll;

create_er_shaws()
{

    set_short("Great Eastroad");
    set_long(
	     "You are walking on a path on the eastern part of the Trollshaws. "+
	     "The forest is getting darker the further in you move. To your northwest "+
	     "a small bridge can be seen. All around you are trees, quite thick, "+
	     "but not as thick as they look further inwards. "
	     );

    add_item(({"eastroad", "road" }),
        "The road is wide, about 3 meters, and seems to be in constant use.\n"
    );
    add_item("bridge", "It's hard to see any details of the small bridge from this distance.\n"
    );
    add_exit(STAND_DIR + "rivend3", "east", 0);
    add_exit(STAND_DIR + "rivend1", "northwest", 0);

    troll = clone_object(TROLLSH_DIR + "npc/conf_troll");
    troll->move(TO);
    
}

reset_rom()
{
   if(!troll)
   {  
       troll = clone_object(TROLLSH_DIR + "npc/conf_troll");
       troll->move(TO);
   }
}
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
