/*
 * Storage room for Warlock shop
 * Finwe, August 2017
 *
 * Changes:
 * 2021-10-03 - Cotillion
 * - Add /lib/store_support
 */

#include "/d/Faerun/defs.h"
#include "../guild.h";

inherit "/std/room";
inherit "/lib/store_support";

void
create_room() 
{
    set_short("The Warlock Guild storage room");
    set_long("This is where sold items at the Warlock shop land. No mortal " +
        "has access to this room.\n");
    add_exit(WARLOCK_ROOMS_DIR + "shop", "out");
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    store_update(obj);
}


public void
reset_room()
{
    reset_store();
}

