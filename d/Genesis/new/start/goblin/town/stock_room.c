/*
 * File         : /d/Genesis/new/start/goblin/town/stock_room.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : October 4, 1999
 * Modifications: 
 * Purpose      : The store room for the Kalerus Shop
 * Related Files: 
 * Comments     : 
 * TODO         : 
 */

inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>

#define MIRROR "/d/Genesis/doc/examples/obj/mirror"
#define TORCH  "/d/Genesis/doc/examples/obj/torch"

void
create_room() 
{
    set_short("You are in the stock room of the Kalerus Shop");

    set_long("You are in the stock room of the Kalerus Shop.\n" +
        "This room is used to store all items that are for " +
        "sale in the Kalerus Shop. Each reset, the stock is " +
        "replenished to contain one mirror and four torches. Notice " +
        "that since we set one mirror, it will always be one mirror, " +
        "but four torches may also be three or five.\n");

    add_exit("/d/Genesis/new/start/goblin/town/shop", "south");

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
