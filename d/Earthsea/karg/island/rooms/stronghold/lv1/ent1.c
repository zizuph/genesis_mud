#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Before stronghold gates");
 set_long("You are standing before gates of great stronghold, built "+
  "by kargish invaders. It's truly amazing , and looks very sturdy. "+
  "The gates towards north lead into the stronghold, while to "+
  "south you see bridge over the moat.\n");

 add_item(({"arch","gate","gates"}),"Sturdy wooden gates can easily "+
   "block entrance to any unwelcomed creature.\n");
 add_item("stronghold","It was built by kargs , as an outpost of "+
   "kargish attacks on Gont. The stronghold looks very sturdy and "+
   "impossible to break in. On the top of arch leading into the "+
   "stronghold you see flowing in the wind flag of Karg Empire.\n");

 add_exit(STRHOLD_LVL1+"ent2","north");
 add_exit(ISLAND_DIR+"rooms/forest/bridge2","south");
}

