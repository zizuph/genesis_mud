/*
 * Frogmorton shop
 * By Finwe, September 1998
 */    

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/sys/shop_items.c"
#include "defs.h"
 
void
create_shire_room()
{
    config_default_trade();
    set_money_greed_sell(90);
    set_money_greed_buy(90);
    set_money_give_out(({10000, 500, 10, 2}));
    set_money_give_reduce(({0, 4, 20, 15}));
    set_short("Frogmorton Sundries");
    set_long( "This is the Sundries shop of Frogmorton. Hobbits " +
        "from the village come here often to buy and sell items " +
        "they make or to buy things they need. The room is " +
        "large with a display case to show off the wares. To " +
        "see what is available you may 'list' the items here.\n");
 
    add_item( ({ "case", "display case" }),  
      "The case has some items for sale. You may 'list' them to " +
      "what is available.\n");
 
    add_item(({"up", "ceiling"}),
        "The ceiling is peaked and made of wood slats\n");
    add_item(({"down", "ground", "floor"}),
        "The floor is made of wood planks. They are swept clean.\n");
    add_item(({"wall", "walls"}), 
        "The walls are made of vertical wood planks.\n");
    add_item(({"planks", "slats"}),
        "They are yellow from age and look like they were " +
        "from beech.\n");
 
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(FROG_DIR + "road04", "out",0,0,1);
    add_exit(FROG_DIR + "road04", "south");    
 
    config_default_trade();
    set_store_room(FROG_DIR + "store");
    set_standard_equip(FROG_EQUIP);

}
 
void
init()
{
    ::init();
    init_shop();
}
