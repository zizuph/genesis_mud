
 /* The store room for the fish monger's store 
    Coded by:  Jaacar
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
    set_short("The Fish Monger's storeroom");
    set_long("This is the storeroom for the Fish Monger's shop.  "+
        "How the hell did you get in here?!  Get out! <grin>\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(BEACH+"village8","north",0,0);
}
