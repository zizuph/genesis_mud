/*
 * Shop of the Trollshaws
 * Finwe, September 2001
 */
 
#pragma save_binary

#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

inherit TUNNEL_BASE;
//inherit "/d/Shire/std/room.c"; 
inherit "/d/Emerald/lib/shop_list";
 

/* Prototype */
void reset_shire_room();
 
static object shopkeeper;  
 
 
void
create_tunnel_room()
{
    add_prop(ROOM_S_MAP_FILE, "trollshaws2.txt");

    set_short("A collapsed tunnel");
    set_long("This is a collapsed tunnel deep in the Trollshaws. " +
        "At one time it was a well maintained but now is nothing " +
        "more than a hole in a side passage. Trolls come here and " +
        "sell loot they no longer want or is worthless to them.\n");
 
    config_default_trade();
    set_money_give_max(1000); /* Else things go wrong with "sell all" */
                          /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 1000,  700, 4000,    1 })); /* Max_pay   */
    set_money_give_reduce(({    2,    7,    4,    4 })); /* Threshold */

    set_money_greed_sell(105); /* players paid this when selling */
    set_money_greed_buy(95);
    set_store_room(TUN_DIR + "store");

    set_alarm(1.0, 0.0, reset_shire_room);
     
    add_exit(TUN_DIR + "tc11", "north");
    add_exit("@@query_store_room@@", "south" , "@@wiz_check@@", 0,1);
 
}
 
void
reset_shire_room()
{
/* 
    if (!shopkeeper)
        shopkeeper = clone_object(NPC_DIR + "shopkeeper");
    if (!present(shopkeeper,this_object()))
        shopkeeper->move(this_object());
*/ 
}
 
 
 
void
init()
{
    ::init();
 
    init_shop();
 
}
