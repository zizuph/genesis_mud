/*
 * Storage room for Fire knives shop
 * 
 * Cotillion - 2020-08-31
 * - Made this an actual store.
 *
 *  Edited for Phlan by Tharizdun Jan 2021
 */

#include "/d/Faerun/defs.h"
/* #include "../guild.h";
*
*  edited out*/

inherit "/std/room";
inherit "/lib/store_support";

void
create_room() 
{
    set_short("The Phlan shop store room");
    set_long("This is where sold items at the Phlan shop land. No mortal " +
        "has access to this room.\n");
        
    add_exit(PHLAN_ROOMS_DIR + "phlanshop", "out");
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    store_update(obj);
}

