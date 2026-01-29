// file name: shore24
// creator: Ilyian, September 21, 1995
// last update: room along the Shore path around the
//              Isle of the Dead
// purpose:
// note: Most of the code for this room is contained
//       in the inherited file /d/Avenir/common/dead/dead.c
// bug(s):
// to_do:

inherit "/d/Avenir/common/dead/dead.c";
#include "../dead.h"
object merchant;
void
create_room()
{
   shore_long("The path turns from the south to the "
             +"northwest here, following the shape "
             +"of the irregular shoreline. West "
             +"lie the dark moors, and to the south "
             +"the path seems to end at the base of a "
             +"sheer cliff."); 
   AI(({"cliff","cliffs"}),"The cliffs rise up to the "
             +"south at the end of the path. There seems "
             +"to be some sort of gate at the end of the "
             +"path.\n");
   AI(({"gate","gates"}),"There seems to be a gate into "
             +"the cliff at the end of the path to the "
             +"south.\n");

   shore_exit("south","25");
   shore_exit("northwest","23");
   shore_marsh("west","53");

   reset_room();
}

void
reset_room()
{
       seteuid(getuid());
	   if (!merchant)
	   {
		   merchant=clone_object(MON+"merchant");
		   merchant->move_living("X", TO);
	   }
   shore_reset();
}
