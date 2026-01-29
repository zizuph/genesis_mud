/* Storeroom for gift shop */

inherit "/std/room";
inherit "/lib/store_support";

#include "../local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
create_room()
{
    set_short("The shop's store room");
    set_long("This is the store room for the shop.\n");

    add_exit(KROOM + "hoopak_store", "west");

    INSIDE;
    reset_room();
}

void
reset_room()
{
    return;
}
