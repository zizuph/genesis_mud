/*
 * Shop of Bree
 * Revamped by Finwe, March 1999
 * The old shop is shop_old.c
 *
 * Added 'list standard equipment' to shop
 * -- Finwe October 2005
 *
 *
 * Palmer May 7, 2005
 * Changed 'out' exit to 'south' 
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";
//inherit "/d/Emerald/lib/shop_list";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/sys/shop_items.c"
#include "defs.h"

#define STORE_ROOM (TOWN_DIR + "shop_store")
/*
#define BREE_EQUIP ({	STAND_OBJ + "shoptorch", \
    STAND_WEAPON + "shopsword", \
    STAND_OBJ + "sack", \
    STAND_OBJ + "ink", \
    STAND_OBJ + "quill", \
    STAND_OBJ + "paper", \
	STAND_OBJ + "backpack", })
*/
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

    add_exit(ROAD_DIR + "broad05", "south", 0);
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

