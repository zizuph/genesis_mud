/*
 * Dol Guldur shop storage room
 * /d/Gondor/rhovanion/dolguldur/shop2.c
 *
 * Varian - November 2020
 */

#include "/d/Gondor/rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit RHOVANION_DIR + "dolguldur/std/room";

void
create_room()

{
    set_short("Storage room for Dol Guldur shop");
    set_long("Hey, are you a wizard? You shouldn't be here unless you are! This is " +
        "just the storage room for the shop in Dol Guldur.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(DG_DIR + "shop", "west", "@@shop@@", 3, 0);
}

int
shop()
{
    write("\n\nYou go back to the shop where you belong\n\n");
    return 0;
}