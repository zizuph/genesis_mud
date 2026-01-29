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
    set_short("a sandy beach on Tolfalas island, in the Bay of Belfalas");
    set_long(&long_desc());
    add_prop(ROOM_I_NO_CLEANUP,1);
    add_exit(TOLFALAS_DIR + "room/beach5", "northwest", 0, 2);
    add_exit(TOLFALAS_DIR + "room/beach3", "south", 0, 2);
    beach_add_items();
    sky_add_items();
    add_beach_tells();
    set_tell_time(300);
    reset_room();
}

string
long_desc()
{
    return "On a rocky beach on Tolfalas Island, in the Bay of Belfalas." +
        sky_desc() + " The shoreline is narrow and strewn with jagged " +
        "rocks, making passage difficult. Cliffs of black rock rise from " +
        "the shoreline.\n"; 
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
        sky_add_items();
}
