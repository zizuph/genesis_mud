/* armrstor.c: The storeroom of the Tyr armour merchant */
inherit "/std/room";
inherit "/lib/store_support";
#include "defs.h"

#define LTHRJRKN (ATH_ARMOUR+"body_lth")
#define STDDDVST (ATH_ARMOUR+"body_std")

void create_room()
{
    set_short("the storeroom of the armour merchant");
    set_long("On racks hang all the armours bought and sold by "+
             "the armour merchant of Tyr.\n");
    INSIDE
    add_exit(TZ_CARAVAN+"armrmrch.c", "south", 0, 1);
    clone_object(LTHRJRKN)-> move(TO, 1);
    clone_object(LTHRJRKN)-> move(TO, 1);
    clone_object(STDDDVST)-> move(TO, 1);
}

void enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    store_update(obj);
}
