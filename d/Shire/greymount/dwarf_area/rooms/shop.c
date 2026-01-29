/*
** Dwarven Mining Company Shop
** Created By Leia
** February 17, 2005
** Based On The Bree Shop
*/

#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/sys/shop_items.c"
#include "../defs.h"

void reset_shire_room();

void
create_shire_room()
{
    set_short("Dwarven Mining Company Supply Shop");
    set_long("Looking around you find yourself inside of a large carved out store. The counter, display cases, and everything else is carved out of the stone of the mountain. The only thing that isn't stone in this place is the glass on the cases and the pricelist. There are many items on display and ready to be bought. The shopkeeper stands ready to assist you in any way.\n");

    add_item(({"list","pricelist","prices"}), "@@price_long");

    add_item(({"item","items"}),
       "The large number of items causes you to not be able to focus on one or two of them. Perhaps you should read the pricelist to get a better idea of what you can buy.\n");

    add_item(({"owner","store owner", "shopkeeper"}),
       "The suspicious looking dwarf is watching you closely, so you do not get the chance to steal anything. Other than that, he waits patiently for you to decide upon an item.\n");


    add_exit(DT18, "south");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    config_default_trade();  /* Set up the trading system */
                          /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 100,    700, 4000,    0 })); /* Max_pay   */
    set_money_give_reduce(({     0,     7,    4,    4 })); /* Threshold */
    set_store_room(SHOP_STOR);

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