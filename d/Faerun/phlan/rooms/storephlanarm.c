/*
 * Storage room for Fire knives shop
 * 
 * Cotillion - 2020-08-31
 * - Made this an actual store.
 *
 *  Edited for Phlan by Tharizdun Jan 2021
 */

#include "/d/Faerun/defs.h"
#include <defs.h>


inherit "/std/room";
inherit "/lib/store_support";

void
create_room() 
{
    set_short("The Phlan armour shop store room");
    set_long("This is where sold items at the Phlan armour shop land. No mortal " +
        "has access to this room.\n");
        
    add_exit(ROOM_DIR + "phlanarmshop", "out");
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    store_update(obj);
}

