/*
 * Shop of Bree
 * Revamped by Finwe, March 1999
 * The old shop is shop_old.c
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";
inherit "/d/Emerald/lib/shop_list";

#include "/d/Shire/sys/defs.h"
#include "defs.h"

//#define STORE_ROOM (TOWN_DIR + "shop_store")
#define STORE_ROOM ("/w/finwe/hell")

static object shopkeeper;  

/* Prototype */
void reset_shire_room();

void
create_shire_room()
{
    set_short("Bree Tools & Supplies");
    set_long("You have entered the local shop in the village Bree. This sure is an old, special place. In this tools and supplies shop you can buy or sell all kinds of things. On the wall is a poster listing supplies that may be purchased \n");

    add_item(({"list","pricelist","prices"}), "@@price_long");

    add_item(({ "poster",}), "There is some writing on it. Maybe " +
        "you should read it.\n");
    add_cmd_item(({"poster"}), "read", "@@poster_desc@@");


    add_item(({"item","items"}),
       "There are far too much items lying around to pick one out of. You "
     + "should better take a look at the pricelist, to get an idea of what "
     + "useful stuff you can buy here.\n");

    add_item(({"owner","store owner"}),
       "The hobbit is watching you closely, so you do not get "
     + "the chance to steal anything. Besides that, he leaves you on your "
     + "own to check out the stuff that is lying around.\n");

    add_exit(ROAD_DIR + "broad05", "out", 0);
    add_exit(ROAD_DIR + "broad05", "south", 0, 1, 1);    
    add_exit(STORE_ROOM, "north", "@@wiz_check",0,1);

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    config_default_trade();  /* Set up the trading system */
                          /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 100,    700, 4000,    0 })); /* Max_pay   */
    set_money_give_reduce(({     0,     7,    4,    4 })); /* Threshold */
    set_store_room(STORE_ROOM);
    set_alarm(1.0, 0.0, reset_shire_room);
//    configure_shire_inn();



}

void
reset_shire_room()
{
    if (!shopkeeper)
    {
        shopkeeper = clone_object("/d/Shire/esgaroth/npcs/shopkeeper");
        shopkeeper->move(this_object());
    }

}

void
init()
{
    ::init();
    init_shop();
    init_shire_inn();
}
int
do_order(string str) 
{
    if (!shopkeeper)
    {
        notify_fail("There is no one here to buy anything from. " +
          "The shopkeeper has left to get more supplies.\n");
        return 0;
    }
    return ::do_order(str);
}

int
do_sell(string str) 
{
    if (!shopkeeper)
    {
        notify_fail("There is no one here to sell your supplies to. " +
          "The shopkeeper is gone for the moment.\n");
        return 0;
    }
    return ::do_sell(str);
}


mixed *
get_order(string item_name)
{
    object order;
    int price;

    setuid(); seteuid(getuid());
    
    switch (item_name)
    {
        case "pack":
        case "backpack":
        case "weather worn pack":
        case "weather-worn pack":
        case "weather worn packs":
        case "weather-worn packs":
        case "weather worn backpack":
        case "weather-worn backpack":
        case "weather worn backpacks":
        case "weather-worn backpacks":
            order = clone_object("/d/Shire/common/obj/backpack");
            price = 672;
            break;
    
        case "ink":
        case "inks":
        case "black ink":
        case "black inks":
            order = clone_object("/d/Shire/common/obj/ink");
            price = 71;
            break;

        case "paper":
        case "papers":
        case "piece of paper":
        case "pieces of paper":
            order = clone_object("/d/Shire/common/obj/paper");
            price = 26;
            break;

        case "quill":
        case "quills":
            order = clone_object("/d/Shire/common/obj/quill");
            price = 55;
            break;

        case "sack":
        case "sacks":
        case "rugged sack":
        case "rugged sacks":
//            order = clone_object("/d/Shire/common/obj/sack");
            order = clone_object("/d/Shire/common/obj/shoptorch");

            price = 40;
            break;
    
        case "torch":
        case "torches":
        case "small torch":
        case "small torches":  
            order = clone_object("/d/Shire/common/obj/shoptorch");
            price = 30;
            break;

        return (({order}) + ({price}));
    }
}

string poster_desc()
{
    return "\n"+
        "\t+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n"+
        "\t|                                                    |\n"+
        "\t|   O                                            O   |\n"+
        "\t|                    Bree Supplies                   |\n"+
        "\t|                                                    |\n"+
        "\t|    Below is equipment every well supplied          |\n"+
        "\t|    traveller needs. They may be purchased here.    |\n"+
        "\t|                                                    |\n"+
        "\t|    ----------------------------------------------  |\n"+
        "\t|    A piece of paper . . . . . . . .      2c   2c   |\n"+
        "\t|    A quill. . . . . . . . . . . . .      4s   7c   |\n"+
        "\t|    A small torch. . . . . . . . . .      2s   6c   |\n"+
        "\t|    A weather-worn backpack. . . . .  4gc 8s   0c   |\n"+
        "\t|    An old rugged sack . . . . . . .      3s   4c   |\n"+
        "\t|    Black ink. . . . . . . . . . . .      5s  11c   |\n"+
        "\t|                                                    |\n"+
        "\t|   O                                            O   |\n"+
        "\t|                                                    |\n"+
        "\t+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n\n";
}
