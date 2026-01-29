/*
 * Shop of Greenfields
 * Revamped by Finwe, December 2000
 * The old shop is shop_old.c
 *
 * 2000/12/31 Last update
 * 2011/08/02 Lavellan - Reinstated pricelist
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";
inherit "/d/Emerald/lib/shop_list";


#define STORE_ROOM (GREEN_DIR + "shop_store")
#include "/d/Shire/common/defs.h"
/* Prototype */
string show_list();
void reset_shire_room();

void
create_shire_room()
{
   set_short("The Greenfields Sundries Shop");
   set_long("The Greenfields Sundries Shop is a quiet place, full of antiques "+
   "and relics from battles long ago.  The store owner is hunched behind the "+
   "counter, perfectly happy to let you wander around and examine the "+
   "merchandise.  A helpful sign has been posted to the wall.\n");

   add_item("wall","It has the pricelist pinned to it.\n");

//    add_item(({"list","pricelist","prices"}), "@@price_long");
    add_item(({"pricelist","prices"}), show_list);
    add_cmd_item(({"pricelist","prices"}), "read", show_list);
    add_item(({"sign", "helpful sign"}), "It has helpful information on it, " +
        "which you could read.\n");

    add_item(({"item","items","antiques","relics"}), break_string(
       "There are far too many items lying around to pick one out of. You "
     + "should better take a look at the pricelist, to get an idea of what "
     + "useful stuff you can buy here.\n",70));

    add_item(({"owner","store owner"}), break_string(
       "The hobbit is fast asleep, his feet laid up on "
     + "the counter.  Not worried about you, he leaves you on your "
     + "own to check out the stuff that is lying around.\n",70));

   add_item("counter","Above the counter you see two tiny hobbit "+
   "feet lazily perched.\n");
    add_exit(GREEN_DIR + "vill2","west",0);
    add_exit("/d/Shire/greenfields/shop_store","north","@@wiz_check@@");

    add_prop(ROOM_I_INSIDE,1);	/* This is a real room */

    config_default_trade();  /* Set up the trading system */
    set_money_give_max(1000); /* Else things go wrong with "sell all" */
			  /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 10000,   700,  40,    1 })); /* Max_pay   */
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

string
show_list()
{
    do_list("");
    return "";
}