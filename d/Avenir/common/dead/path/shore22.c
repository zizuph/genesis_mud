// file name: shore22
// creator: Ilyian, September 21, 1995
// last update: room along the Shore path around the
//              Isle of the Dead
// purpose:
// note: Most of the code for this room is contained
//       in the inherited file /d/Avenir/common/dead/dead.c
// bug(s):
// to_do: Add some sort of summoning ritual for the
//        demon Hizarbin

inherit "/d/Avenir/common/dead/dead.c";
#include "../dead.h"

void
create_room()
{
   shore_long("The shoreline juts out to the north "
             +"here, ending in the sharp bend from "
             +"the southwest to the southeast. The ground "
             +"seems a bit more rough here than other "
             +"places along the path. To the south, "
             +"a small hillock rises out of the swamp."); 
   set_short("promontory");
   
   AI(({"hill","hillock"}),"The small hillock rises out "
             +"of the dismal swamp to the south. There seems "
             +"to be a large shape at the top of it.\n");
   AI(({"shape"}),"You cannot make it out from here.\n");

   shore_exit("southwest","21");
   shore_exit("southeast","23");
   shore_marsh("south","_hill");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
