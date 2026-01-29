/*
 * Shop of Bree
 * Revamped by Finwe, March 1999
 * The old shop is shop_old.c
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";
inherit "/d/Emerald/lib/shop_list";


#define STORE_ROOM (STAND_DIR + "shop_store") /* Where the items are stored  */
#include "defs.h"
/* Prototype */
void reset_shire_room();

void
create_shire_room()
{
    set_short("Bree Tools & Supplies");
    set_long("You have entered the local shop in the village Bree. "
     + "This sure is an old, special place. The shopkeeper, an old "
     + "Bree-hobbit, looks curiously at you from the corner. In this "
     + "tools and supplies shop you can buy or sell all kinds of things. "
     + "The shopkeeper keeps track of all items on a pricelist, together "
     + "with their price. If you want the shopkeeper's opinion on something, "
     + "ask him to value it.\n");

    add_item(({"list","pricelist","prices"}), "@@price_long");

    add_item(({"item","items"}), 
       "There are far too much items lying around to pick one out of. You "
     + "should better take a look at the pricelist, to get an idea of what "
     + "useful stuff you can buy here.\n");

    add_item(({"owner","store owner"}), 
       "The hobbit is watching you closely, so you do not get "
     + "the chance to steal anything. Besides that, he leaves you on your "
     + "own to check out the stuff that is lying around.\n");

    add_exit(STAND_DIR + "townrm", "west", 0);
    add_exit(STORE_ROOM, "north", "@@wiz_check");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    config_default_trade();  /* Set up the trading system */
    set_money_give_max(1000); /* Else things go wrong with "sell all" */
                          /* Copper Silver Gold Platinum  */
//    set_money_give_out(   ({ 10000,   700,  40,    1 })); /* Max_pay   */
    set_money_give_out(   ({ 100,   70,  400,    1 })); /* Max_pay   */
    set_money_give_reduce(({     0,     7,   4,    4 })); /* Threshold */
    set_store_room(STORE_ROOM);


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
