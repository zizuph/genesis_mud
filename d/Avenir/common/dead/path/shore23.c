// file name: shore23
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

void
create_room()
{
   shore_long("The path bears southeast, and to the "
             +"northwest it heads out to a "
             +"sharp promontory. To the south "
             +"lie the grim moors, and west a "
             +"small hillock rises out of the "
             +"swamp."); 
   AI(({"promontory"}),"The shoreline to the northwest "
             +"juts out into the water like a crooked "
             +"finger.\n");
   AI(({"hill","hillock"}),"The small hillock rises out "
             +"of the dismal swamp to the west. There seems "
             +"to be a large shape at the top of it.\n");
   AI(({"shape"}),"You cannot make it out from here.\n");

   shore_exit("northwest","22");
   shore_exit("southeast","24");
   shore_marsh("west","_hill");
   shore_marsh("south","53");

   reset_room();
}

void
reset_room()
{
   shore_reset();
}
