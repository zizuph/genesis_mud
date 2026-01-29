/* 
 * /d/Kalad/common/
 * Purpose    : 
 * Located    : 
 * Created By : 
 * Modified By: 
 */

#include "/d/Kalad/defs.h"
#include <cmdparse.h>
#pragma save_binary

inherit "/d/Kalad/room_std";
inherit "/lib/shop.c";
inherit  "/d/Kalad/std/shop_list"; 

#define STORE_ROOM "/d/Kalad/common/market/shop/potion_store"


void
create_room()
{
    config_default_trade();
    set_money_give_max(5000);
    set_money_give_out(({5000, 5000, 500, 10}));
    set_money_give_reduce(({25, 25, 20, 5}));
    set_store_room(STORE_ROOM);

    set_short("The shop of Eron von Lotto");
    
    set_long("\n"+
    "   You have entered a large and messy room that looks as if it "+
    "belongs to some kind of mad scientist. There are tables scattered "+
    "everywhere on the walls, on which rest many vials and flasks. On "+
    "the floor, you step through piles of broken glass along strange "+
    "black stains. There are also large burnt spots in the wood on the "+
    "walls, and you wonder what could have done such a thing. The air "+
    "is filled with strange scents. On the center table, you "+
    "see a pricelist.\n\n");
    add_item("pricelist","@@shoplist@@");
    add_cmd_item("pricelist","read","@@shoplist@@");
    add_item("tables","There are tables along the walls covered with "+
    "strange flasks and vials of liquid and powders. In the center of "+
    "the room is the main table, where you see bags of money sitting.\n");
    add_item(({"vials","flasks"}),"The vials and flasks around the room "+
    "are filled with many strange liquids of various color, as well as "+
    "powders and even strange things.\n");
    add_item(({"piles","broken glass","glass"}),"There are piles of "+
    "broken glass, most likely from old vials and flasks.\n");
    add_item(({"stains","black stains","strange stains"}),"The stains "+
    "on the ground are mysterious indeed. You wonder what could have "+
    "made them.\n");
    add_item(({"spots","burnt spots"}),"The large burnt spots on the "+
    "walls look to have been caused by intense heat.\n");
    add_item("walls","The walls are made of old wood, and have strange "+
    "burnt spots on them.\n");
    add_item("floor","The floor is made of stone and is covered with "+
    "piles of broken glass.\n");
    add_item("ceiling","The ceiling is of wood.\n");
    add_cmd_item("air","smell","The air is filled with the scents of "+
    "herbs, spices and sulfur.\n");

    INSIDE;

    set_money_greed_buy(100);
    set_money_greed_sell(50);

}

string
shoplist()
{
    return 
    "         Welcome to Eron von Lotto's Potion Shop!        \n"+
    "Here I will only buy and sell potions!\n"+
    "You can 'list' potions to see what I have in stock.\n"+
    "You can 'sell' or 'buy' potions as you like.\n"+
    "Remember, magic is special, and thus valuable!\n";
}


void
init()
{
    ::init();
    init_shop();
}


int
shop_hook_allow_sell(object ob)
{
    if( !stringp(ob->query_potion_name()) )
    {
        write("I will only deal in potions!\n");
        return 0;
    }
    return 1;
}
	

/*
 * Function name: query_buy_price
 * Description:   What price should the player pay
 * Arguments:     ob - The object to test
 * Returns:       The price
 */
int
query_buy_price(object ob)
{
    int seed;
 
    sscanf(OB_NUM(ob), "%d", seed);
    return 2 * ob->query_potion_value() * (query_money_greed_buy() +
        15 - this_player()->query_skill(SS_TRADING) / 4 +
        random(15, seed)) / 100;
}
 
/*
 * Function name: query_sell_price
 * Description:   What price will the player get when selling an object?
 * Arguments:     ob - The object
 * Returns:       The price
 */

int
query_sell_price(object ob)
{
    int seed;
 
    sscanf(OB_NUM(ob), "%d", seed);
    return ob->query_potion_value() * 100 / (query_money_greed_sell() +
        15 - this_player()->query_skill(SS_TRADING) / 3 +
        random(15, seed + 1)); /* Use another seed than on buying */
}
 
