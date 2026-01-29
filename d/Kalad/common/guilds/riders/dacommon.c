inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Mhyrkhaan */

void
create_room()
{
    ::create_room();
    set_short("Common room of the Dark Alliance");
    set_long("You are in the common room of the Dark Allaince. The room "+
    "is made of black stone, there are two portals in here, in one "+
    "you see the wavering image of the Dark Alliance Guildhall, in the "+
    "other you see a buletin board. The portals themselves provide you "+
    "with more than enough light to work by.\n");
    add_exit(COMMON(guilds/riders/rhall),"back",0,-1,-1);
    clone_object("/d/Genesis/obj/board")->move(TO,1);
}

