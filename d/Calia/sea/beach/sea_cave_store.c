
 /* 
    The store room for Ripper's sea cave shop. 

    Coded by:  Maniac, 28/9/96
 */

inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "defs.h"

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
create_room()
{
    set_short("The Sea Cave Storeroom");
    set_long("This is the storeroom for Ripper's sea cave shop.\n"); 

    add_prop(ROOM_I_INSIDE,1);

    add_exit(BEACH+"sea_cave","south",0,0);
}


