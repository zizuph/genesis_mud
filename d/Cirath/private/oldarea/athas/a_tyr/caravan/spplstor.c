/* spplstor.c: The storeroom of the Tyr supply bizarre */
inherit "/std/room";
inherit "/lib/store_support";
#include "defs.h"

void
create_room()
{
    set_short("the storage pit of the supply bizarre");
    set_long("Dumped randomly in this pit are the items sold in the "+
             "bizarre, tossed upwards by a convenient earth elemental.\n");
    INSIDE
    add_exit(TZ_CARAVAN+"spplmrch.c", "up", 0, 1);
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    store_update(obj);
}
