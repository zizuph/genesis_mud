/*
 * /d/Genesis/doc/examples/trade/store.c
 *
 * This is the store-room of the example shop.
 *
 * /Mercade, 7 January 1994
 */

/* This is a room, but it is also a store, so inherit the store support
 * library.
 */
inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>

#define MIRROR "/d/Genesis/doc/examples/obj/mirror"
#define TORCH  "/d/Genesis/doc/examples/obj/torch"

void
create_room() 
{
    set_short("the store-cabinet of the example shop.");
    set_long("This cabinet is used as to store all items that are for " +
        "sale in the shop of the example shop. Each reset, the stock is " +
        "replenished to contain one mirror and four torches. Notice " +
        "that since we set one mirror, it will always be one mirror, " +
        "but four torches may also be three or five.\n");

    add_exit("/d/Genesis/doc/examples/trade/shop", "out");

    add_prop(ROOM_I_INSIDE, 1);

    /* With the first calls we set that the store should by default contain
     * one mirror and four torches. Then call reset_store() to make these
     * items available at creation too.
     */
    set_default_stock( ({ MIRROR, 1, TORCH, 4 }) );
    reset_store();
}

/*
 * You should always call store_update() if an object enters the store-
 * room to update it and let it be added to the stock.
 */
void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    store_update(obj);
}

/*
 * To have the default stock replenished at reset, define the function
 * reset_room() to call reset_store().
 */
void
reset_room()
{
    reset_store();
}
