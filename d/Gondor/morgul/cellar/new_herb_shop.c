/*
 *  Herb Shop
 *
 *  Based on the collective works Olorin, Palmer, Toby etc.
 *  Adjusted to use the new common herb shop code.
 *
 *  Eowul, April 29th, 2010
 */
 
inherit "/d/Gondor/morgul/cellar/cellar.c";
inherit "/d/Gondor/morgul/feeling.c";
inherit "/d/Genesis/specials/guilds/lib/herb_shop.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"
#include "/sys/money.h"

#define COIN_TYPES            ({ "cc", "sc", "gc", "pc" })

void create_morgul_cellar_room()
{
    set_room_type("new herb shop");
    set_extra_long("A small lamp gives some light here, illuminating " 
        + "a narrow wooden counter. On the newly re-built counter stands "
        + "a sign. Hooks in the ceiling hold bunches of drying herbs.");
        
    set_level(1);

    add_floor();
    add_walls();
    add_stones();
    add_item(({"roof","ceiling"}),
    	  "From the high vaulted ceiling several hooks and a small "
    	+ "lamp are hanging.\n");
    add_item(({"small shop", "herb shop","shop"}), 
          "This dark and dusty room is a herb shop. Here you can "
        + "buy and sell herbs. But you will probably be robbed in "
        + "the process.\n");
    add_item(({"counter", "wooden counter"}),
          "A simple wooden counter made from rough boards. On the " 
        + "counter, you can see a sign. At the front of the counter "
        + "there is a small plaque.\n");
    add_item(({"lamp", "light"}), 
          "A single lamp hanging from the ceiling tries to give light "
        + "to the room. It is a rather feeble attempt, of course.\n");
    add_item(({"windows"}), "There are no windows here.\n");
    add_item(({"hooks", "hook"}), 
          "Wrought iron. From some of them are hanging dried herbs, "
        + "but they are out of your reach.\n");
    add_item(({"herbs", "herb", "bunches of herbs", "bunches"}), "Herbs, "
        + "tied in bunches, hanging from the ceiling to dry.\n");
    /*
    add_item(({"sign", "poster"}), read_sign());
    add_cmd_item(({"sign", "poster"}), "read", read_sign());
    
    add_item(({"plaque", "small plaque", "small copper plaque", "copper plaque"}), "@@read_plaque");
    add_cmd_item(({"plaque", "small plaque", "small copper plaque", "copper plaque"}), "read", "@@read_plaque");
*/
    add_exit(CELLAR_DIR + "pass_1e2", "southeast", 0);

    add_prop(ROOM_I_LIGHT, 1);   /* A lamp is giving light in here */
    add_prop(ROOM_I_HIDE, 25);   /* But it's not much light, so it's easy to hide */

    set_store_room(VOID_OBJECT);
    
    config_default_trade();
    set_money_give_max(5000);
    set_money_give_out(({1000, 5000, 5000, 10}));
    set_money_give_reduce(({4, 0, 20, 15}));
    set_money_greed_buy(100);
    set_money_greed_sell(100);
}

void init()
{
    ::init();
    init_shop();
}

string hook_print_herb_header()
{
    return "   //======\\\\ We sell the following herbs of the requested "
        + "type: //=======\\\\\n\n";
}

private string money_text(int am)
{
    int    *arr = MONEY_SPLIT(am),
            ind = sizeof(MONEY_TYPES);
    string  txt = "";

    while (--ind >= 0)
    {
        if (arr[ind])
            txt += sprintf("%2d %2s ", arr[ind], COIN_TYPES[ind]);
        else
            txt += "      ";
    }

    return txt;
}

public string
hook_print_herb_item(object herb_object)
{
    return sprintf("\t%4d %-'.'34s %s\n",
        query_herb_quantity(herb_object),
        capitalize(herb_object->query_herb_name()),
        money_text(this_object()->query_buy_price(herb_object)));
}


string hook_print_herb_footer()
{
    return "\n   \\\\======================================================="
        + "==============//\n";
}

void convert_old_herb_shop_data() 
{
    mapping old_data = restore_map(CELLAR_DIR + "herb_store");
    herb_list = old_data["herbs"];
    save_herb_data();
}