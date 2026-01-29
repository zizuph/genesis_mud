/*
 * Bandit shop
 * -- Finwe, September 2006
 */

#pragma strict_types

inherit "/d/Faerun/highroad/bandits/std/base_cave.c";

#include "/d/Faerun/defs.h"
#include "defs.h"
#include "/d/Faerun/sys/shop_items.c"

//inherit BASE_CAVE;

#define STORE_ROOM "/d/Faerun/highroad/bandits/rooms/store" 

static object  keeper;


void
create_cave()
{
    add_prop(ROOM_I_INSIDE,1);
    ALLOW_STEEDS;
    set_short("a wide cave");
    set_long("This wide cave is larger than the other caves. Bandits come here and sell stuff they have stolen from travellers. The walls are rough and the ceiling higher than the other caves.\n");

    config_default_trade();
    set_money_greed_sell(95);
    set_money_greed_buy(95);
    set_store_room(STORE_ROOM);
    // this sets standard equipment when morts do 'list equipment'
    // see /d/Faerun/sys/shop_items.h to see what items are available.
    set_standard_equip(BANDIT_EQUIP);
    
    reset_room();


    add_exit(CAVE_DIR + "entr", "north");
    add_exit(CAVE_DIR + "bank", "south");


}

void
init() 
{
    ::init();
    init_shop();
}

void reset_room() 
{ 
    if(!keeper)
        keeper = clone_object(NPC_DIR + "shopkeeper");
    keeper->move(TO);

}
