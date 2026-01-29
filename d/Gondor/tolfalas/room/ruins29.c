/*
 * /d/Gondor/tolfalas/room/beach1.c
 *
 *  Palmer - 12 Aug 2006
 *  
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/tolfalas/lib/room_funcs.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public string long_desc();

public void
create_gondor()
{
    set_short("ancient ruins on Tolfalas island, in the Bay of Belfalas");
    set_long(&long_desc());
    add_prop(ROOM_I_NO_CLEANUP,1);



    add_exit(TOLFALAS_DIR + "room/ruins30", "east", 0, 2);
    add_exit(TOLFALAS_DIR + "room/ruins34", "southwest", 0, 2);
    add_exit(TOLFALAS_DIR + "room/ruins21", "northeast", 0, 2);
    add_exit(TOLFALAS_DIR + "room/ruins22", "north", 0, 2);
    add_exit(TOLFALAS_DIR + "room/ruins33", "south", 0, 2);
    add_exit(TOLFALAS_DIR + "room/ruins28", "west", 0, 2);
    add_exit(TOLFALAS_DIR + "room/ruins32", "southeast", 0, 2);
    add_exit(TOLFALAS_DIR + "room/ruins23", "northwest", 0, 2);

    ruins_add_items();
    sky_add_items();
    add_ruins_tells();
    set_tell_time(300);
    reset_room();
}

string
long_desc()
{
    return "Among ancient ruins on Tolfalas Island, in the Bay of Belfalas." +
        sky_desc() + "\n"; 
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
        sky_add_items();
}
