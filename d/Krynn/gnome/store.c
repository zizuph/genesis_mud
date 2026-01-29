/*
 *   The storage room of the Solamnian drugstore
 */

inherit "/std/room";
inherit "/lib/store_support";

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include "/sys/stdproperties.h"

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

public void
reset_room()
{
    reset_store();
}

create_room()
{
    set_short("The shop's store room");
    set_long("This is the store room for the shop.\n");

    add_exit(TDIR + "shop","west");

    set_default_stock( ({ OBJ + "torch", 5, OBJ + "helmet", 2, OBJ + "gauntlets", 2,
        OBJ + "clipb", 4, OBJ + "cloak", 2, OBJ + "blast_goggles", 3,
        OBJ + "box_cloner", 2, "/d/Krynn/common/scrolls/shatter_scroll", 1 }) );

    INSIDE;
    LIGHT;
    reset_room();
}


