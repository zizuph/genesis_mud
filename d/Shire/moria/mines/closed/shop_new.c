/*
 * Shop of Moria
 * Revamped by Finwe, December 2000
 * The old shop is shop_old.c
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";
inherit "/d/Emerald/lib/shop_list";
#include "defs.h"


#define STORE_ROOM (THIS_DIR + "shop_store") /* Where the items are stored  */
/* Prototype */
void reset_shire_room();

void
create_shire_room()
{
    set_short("Ugluk Dumwa's Pawnshop and Antiques");
    set_long("You have entered the remains of an old Shop " +
	     "inside the Mines of Moria. It looks just like a " +
	     "typical dwarven shop, except the smell and aura " +
	     "of the new inhabitants of Moria: Orcs. Behind a " +
	     "desk, the new shopkeeper, a subtle and cunning " +
	     "orc with name Ugluk measures you carefully. " +
	     "With a foul writing he has scratched some symbols " +
	     "onto the wall, a sign of some sort.\n");

//   add_item("wall","It has the pricelist pinned to it.\n");

//    add_item(({"list","pricelist","prices"}), "@@price_long");

    add_item(({"item","items"}), 
       "There are far too much items lying around to pick one out of. You "
     + "should better take a look at the pricelist, to get an idea of what "
     + "useful stuff you can buy here.\n");

    add_item(({"owner","store owner","ugluk"}), 
	"The Orc, Ugluk obviously, measures you carefully, and " +
	"by the looks of him, you would guess that it is no " +
	"accident which makes him the grand keeper of this Shop. ");

    add_item(({"desk", "instructions"}), 
	     "It seems like a sturdy desk.\n");

    add_exit(THIS_DIR + "stneslab", "west", 0);
    add_exit(STORE_ROOM, "north", "@@wiz_check");

    add_prop(ROOM_I_INSIDE,1);	/* This is a real room */
    add_prop(ROOM_I_LIGHT, 2);

    config_default_trade();  /* Set up the trading system */
    set_money_give_max(1000); /* Else things go wrong with "sell all" */
			  /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 700,   10000,  40,    1 })); /* Max_pay   */
    set_money_give_reduce(({	 0,	7,   4,    4 })); /* Threshold */
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
