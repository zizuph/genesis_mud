/*
 * Storage room for Fire knives shop
 * 
 * Cotillion - 2020-08-31
 * - Made this an actual store.
 *
 *  Nerull 2019
 */

#include "/d/Faerun/defs.h"
#include "../guild.h";

inherit "/std/room";
inherit "/lib/store_support";

void
create_room() 
{
    set_short("The FK shop store room");
    set_long("This is where sold items at the FK shop land. No mortal " +
        "has access to this room.\n");
        
    add_exit(FIREKNIVES_ROOMS_DIR + "gen_shop", "out");
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    store_update(obj);
}

