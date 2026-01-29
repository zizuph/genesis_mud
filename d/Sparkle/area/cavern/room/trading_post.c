#pragma save_binary

inherit "/std/room";

#include "../goblins.h"

create_room()
{
    set_short("Trading Post");
    set_long(BSN("This is an old trading post.  It seems quite deserted."));
    add_exit("@@map_file|x|57.3y517.3","south",0,0);
}

