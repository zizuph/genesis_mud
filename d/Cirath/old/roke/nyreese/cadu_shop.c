/*
 * cadu_shop.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 *
 * Added to Re-Albi by Ged and Gresolle 92
 * Changed to use /lib/shop by Glindor
 * Updated to use /d/Emerald/lib/shop_list by Finwe, Sept 1996
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/shop";
//inherit "/d/Emerald/lib/shop_list";
//inherit "/d/Genesis/lib/shop_list";

#include "defs.h"

#define STORE_ROOM NYREESEDIR + "cadu_store"

/*
 * Function name:   create_room
 * Description:     Initialize this room
 * Returns:
 */
void
create_room()
{
    config_default_trade();
    set_money_greed_sell(95);
    set_money_greed_buy(95);
    set_money_give_out(({10000, 500, 10, 2}));
    set_money_give_reduce(({0, 4, 20, 15}));
    set_store_room(STORE_ROOM);
    set_short("The Cadu General Store");
    set_long("You are in the Cadu General Store. Here you can trade your " +
             "collected treasures for money or buy new equipment for coming " +
             "adventures. There is a small sign to read with instructions " +
             "on how to use this shop.\n");

    add_item("sign", "A nice looking sign, perhaps you should read it.\n");

    add_exit("cadu_a1",  "south");
    add_exit(STORE_ROOM, "west", "@@wiz_check");

    INSIDE;
}

/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 * Returns:
 */
void
init()
{
    ::init();   /* You MUST do this in a room-init */
    init_shop();
}
