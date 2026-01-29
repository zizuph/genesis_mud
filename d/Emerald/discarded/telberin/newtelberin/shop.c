/*
 * Shop for Telberin
 * Coded by Finwe, January 1997
 * Recoded by Shiva, October 1998
 */
 
#include "defs.h"

inherit TELBERIN_ROOM;
inherit "/d/Emerald/lib/shop_list";

#include <stdproperties.h>
 
int my_greed();
int my_give_out();
int my_give_reduce();
int my_give_max();
string sign_desc();

void
create_telberin_room()
{
    config_default_trade();
    set_money_greed_sell(my_greed);
    set_money_greed_buy(my_greed);
    set_money_give_out(my_give_out);
    set_money_give_reduce(my_give_reduce);
    set_money_give_max(my_give_max);
    set_short("General shop of Telberin");
    set_em_long("Standing in the general shop, you see that this " +
        "place is quite busy. Many wares are sold here, some brought " +
        "from other parts of the world. The shopkeeper stays busy as " +
        "he buys and sells stuff to anyone willing to come here. A " +
        "sign sits on the counter.\n");
 
    add_item("sign", sign_desc);
    add_item("counter", "It is polished to a dark sheen with a " +
        "and a sign on it.\n");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit("tel06_06", "northeast");
 
    set_store_room(TELBERIN_DIR + "store");
}
 
string
sign_desc()
{
    do_read("sign");
    return "";
}

void
init()
{
    ::init();
    init_shop();
}

int
my_greed()
{
    if (this_player()->query_kot_member())
    {
        return 85;
    }

    if (this_player()->query_race_name() == "elf")
    {
        return 95;
    }

    if (this_player()->query_race() == "goblin")
    {    
        return 110;
    }

    if (this_player()->query_race() == "dwarf")
    {
        return 105;
    }
   
    return 100;
}

int *
my_give_out()
{
    if (this_player()->query_kot_member())
    {
        return ({ 10000, 500, 6, 2 });
    }

    if (this_player()->query_race_name() == "elf")
    {
        return ({ 10000, 400, 5, 1 });
    }

    return ({ 10000, 400, 3, 0 });
}

int *
my_give_reduce()
{
    if (this_player()->query_kot_member())
    {
        return ({ 0, 5, 12, 12 });
    }

    if (this_player()->query_race_name() == "elf")
    {
        return ({ 0, 5, 9, 9 });
    }

    if (this_player()->query_race() == "goblin")
    {
        return ({ 0, 2, 5, 5 });
    }
 
    return ({ 0, 2, 8, 8 });
}

int
my_give_max()
{
    if (this_player()->query_kot_member())
    {
        return 2100;
    }

    if (this_player()->query_race() == "elf")
    {
        return 1850;
    }

    return 1728;
}
