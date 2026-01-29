/*
 * Longbottom Shop
 * Based on the Bree shop
 * Finwe, January 2020
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";
//inherit "/d/Emerald/lib/shop_list";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/sys/shop_items.c"
#include "../defs.h"

#define STORE_ROOM (LB_RM_DIR + "shop_store")

/* Prototype */
void reset_shire_room();

void
create_shire_room()
{
    set_short("Longbottom Shop");

    set_long("This is the Longbottom Shop. Hobbits in the area come " +
        "here to buy and sell their wares. The shop is crowded with " +
        "items from all over the Shire. On the wall is a pricelist " +
        "showing things for sale. A shopkeeper stands in a corner and " +
        "watches you curiously to see what you will buy or sell. He will " +
        "give you his opinion on the value of an item if you give it " +
        "to him.\n");

    add_item(({"list","pricelist","prices"}), "@@price_long");

    add_item(({"item","items"}),
       "There are far too much items lying around to pick one out of. You "
     + "should better take a look at the pricelist, to get an idea of what "
     + "useful stuff you can buy here.\n");

    add_item(({"owner","shop owner", "shop keeper", "shopkeeper"}),
       "The hobbit is watching you closely, so you do not get "
     + "the chance to steal anything. Besides that, he leaves you on your "
     + "own to check out the stuff that is lying around.\n");

    add_exit(LB_RM_DIR + "lb02", "southwest", 0);
    add_exit(STORE_ROOM, "north", "@@wiz_check",0,1);

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    config_default_trade();  /* Set up the trading system */
                          /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 100,    700, 4000,    0 })); /* Max_pay   */
    set_money_give_reduce(({     0,     7,    4,    4 })); /* Threshold */
    set_store_room(STORE_ROOM);

    set_standard_equip(BREE_EQUIP);

    room_add_object("/d/Shire/common/obj/trashcan");
}

void
reset_shire_room()
{
}

void
init()
{
    ::init();
    init_shop();
}

