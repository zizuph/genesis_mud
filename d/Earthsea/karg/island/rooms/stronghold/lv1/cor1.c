#include "defs.h"

inherit STD_STRHOLD;

void create_stronghold_room()
{
 set_short("Dark corridor in the stronghold");
 set_long("You are in the dark corridor leading north and south. "+
   "Far away to south you see corridor end and large gates leading "+
   "out of the stronghold. Walls are decorated with banners.\n");

 add_item(({"arch","gate","gates"}),"Sturdy wooden gates can easily "+
   "block entrance to any unwelcomed creature.\n");

 add_item(({"wall","walls"}),"Walls are decorated with colourfull "+
   "banners.\n");
 add_item(({"banner","banners"}),"Banners are of different colours "+
   "and sway slightly in the gusts of wind , freely blowing down "+
   "the corridor.\n");

 add_exit(STRHOLD_LVL1+"ent3","south");
 add_exit(STRHOLD_LVL1+"cor2","north");
}

