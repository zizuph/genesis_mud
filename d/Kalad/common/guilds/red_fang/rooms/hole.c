inherit "/std/room";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_room()
{
    set_short("A tunnel");
    set_long("You are in a dim tunnel, but you see sunlight ahead.\n");
    INSIDE;
    add_exit("/d/Kalad/common/guilds/red_fang/rooms/joinroom", "back");
}

