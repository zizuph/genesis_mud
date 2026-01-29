// file name: shore25
// creator: Ilyian, September 21, 1995
// 
// updates:    Lilith July 2021: updated exit to catacombs
// purpose:
// note: Most of the code for this room is contained
//       in the inherited file /d/Avenir/common/dead/dead.c
// bug(s):

inherit "/d/Avenir/common/dead/dead.c";
#include "../dead.h"

void
create_room()
{
   shore_long("The path ends at a sheer cliff that "
             +"rises up to the south, leading up to "
             +"a solid iron gate that is inset into the "
             +"wall of the cliff. The grey moors lie "
             +"to the west, and the path continues "
             +"to the north."); 
   set_short("near gate in cliff");

   shore_exit("north","24");
   shore_marsh("west","49");
    
// The entrance to the catacombs
   add_exit(CRYPT + "crypt_out","south");

   AI(({"cliff","cliffs","cliffside"}),"The cliff towers "
             +"above you to the south, sheer and "
             +"unclimbable. A hollow has been cut into the side "
			 +"of the cliff. It has a gate blocking the entrance.\n");
    AI("gate", "You need walk farther south to get a better look.\n");
   ACI(({"cliff","cliffs"}),("climb"),"The cliff is too steep "
             +"to climb here.\n");
   
   reset_room();
}

void
reset_room()
{
   shore_reset();
}
