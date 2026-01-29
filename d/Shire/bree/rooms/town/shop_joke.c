/*
 * Joke Shop for April fools, Palmer, March 2003
 * Snarfed from Finwe who snarfed it from:
 * The Bree Inn, Only sells things, does not buy anything
 * 
 */
inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define PRICELIST_ID  ({"pricelist","list","prices"})
#define JOKE_DIR "/d/Shire/jokes/"

/* Prototype */
void reset_shire_room();

static object shop_keeper;

void
create_shire_room()
{
    set_short("The Joke Shop");
    set_long("You have entered Bree's Joke Shop. To celebrate " +
        "April Fool's Day, pranksters, jokers and Shire wizards " +
        "bring their jokes, gags and pranks here to be sold. Items " +
        "may not be returned. We buy nothing here. All use of pranks " +
        "are at your own risk. A sign is posted on one wall, and a poster, " +
        "on another.\n");
    add_item(({"chair", "chairs"}), "The chairs are made out of wood.\n");
    add_item("counter", "It's made out of wood. There is a man standing "+
      "behind it.\n");
    add_item("walls", 
        "The walls are simple, made of wood with a poster on one.\n");
    add_item("poster", "There is some writing on it. Maybe " +
        "you should read it.\n");
    add_cmd_item("poster", "read", "@@pricelist_desc@@");


    add_prop(ROOM_I_INSIDE,1);

    add_exit(ROAD_DIR + "broad03","out");

    set_alarm(1.0, 0.0, reset_shire_room);
    configure_shire_inn();
    add_prop(ROOM_I_NO_CLEANUP,1);
}

// Sign
string
pricelist_desc()
{
    return "\n"+
        "\t+----------------------------------------------------+\n"+
        "\t|                                                    |\n"+
        "\t|   *                                            *   |\n"+
        "\t|                 Bree  Joke Shop                    |\n"+
        "\t|                                                    |\n"+
        "\t|    Below are the items sold here. Items cannot be  |\n"+
        "\t|    returned or sold back here                      |\n"+
        "\t|                                                    |\n"+
        "\t|                                                    |\n"+
        "\t|   *                                            *   |\n"+
        "\t|                                                    |\n"+
        "\t+----------------------------------------------------+\n\n";
}


void
reset_shire_room()
{
    if (!shop_keeper)
        shop_keeper = clone_object(NPC_DIR + "jshop_keeper");
    if (!present(shop_keeper,this_object()))
        shop_keeper->move(this_object());

}

void
init()
{
    ::init();
    init_shire_inn();
}

int
do_read(string str)
{
    if (!str)
        return 0;
    if (member_array(str, PRICELIST_ID) == -1)
        return 0;
    write(pricelist_desc());
    return 1;
}

int
do_order(string str) 
{
    if (!shop_keeper || !present(shop_keeper))
    {
        notify_fail("There is no one here to buy anything from. " +
          "The shopkeeper has left to get more supplies.\n");
        return 0;
    }
    return ::do_order(str);
}


mixed *
get_order(string item_name)
{
    object order;
    int price;

    setuid(); seteuid(getuid());
    switch (item_name)
    {
    case "cloak":
    case "cloaks":
    case "white cloak":
    case "white cloaks":
        order = clone_object(JOKE_DIR + "wcloak");
        price = 450;
        break;
    case "globe":
    case "water globe":
    case "water globes":
    case "globes":
        order = clone_object(JOKE_DIR + "water_globe");
        price = 400;
        break;
    case "pinwheel":
    case "pinwheels":
    case "holiday pinwheel":
    case "holiday pinwheels":
        order = clone_object(JOKE_DIR + "pinwheel");
        price = 100;
        break;
    case "mistletoe":
    case "mistletoes":
    case "branch":
    case "branches":
    case "mistletoe branch":
    case "mistletoe branches":
        order = clone_object(JOKE_DIR + "mistletoe");
        price = 90;
        break;
    case "sash":
    case "festive sash":
    case "sashs":
    case "festive sashes":
        order = clone_object(JOKE_DIR + "sash");
        price = 288;
        break;
    case "crown":
    case "crowns":
    case "ivy crown":
    case "ivy crowns":
        order = clone_object(JOKE_DIR + "crown");
        price = 100;
        break;
// drinks
    case "eggnog":
    case "mug of eggnog":
    case "eggnogs":
    case "mugs of eggnog":
        order = clone_object(JOKE_DIR + "eggnog");
        price = 20;
        break;
    case "hot chocolate":
    case "hot chocolates":
    case "mug of hot chocolate":
    case "mugs of hot chocolates":
        order = clone_object(JOKE_DIR + "hotchoc");
        price = 30;
        break;
    case "cider":
    case "ciders":
    case "spiced cider":
    case "spiced ciders":
    case "mug of spiced cider":
    case "mugs of spiced ciders":
    case "mug of cider":
    case "mugs of ciders":
        order = clone_object(JOKE_DIR + "cider");
        price = 30;
        break;
    case "wine":
    case "wines":
    case "glass of wine":
    case "glasses of wine":
    case "mulled wine":
    case "mulled wines":
    case "glass of mulled wine":
    case "glasses of mulled wine":
        order = clone_object(JOKE_DIR + "mwine");
        price = 40;
        break;
    case "wassail":
    case "wassails":
    case "mug of wassail":
    case "mugs of wassail":
        order = clone_object(JOKE_DIR + "wassail");
        price = 50;
        break;
    case "glogg":
    case "gloggs":
    case "mug of glogg":
    case "mugs of glogg":
        order = clone_object(JOKE_DIR + "glogg");
        price = 65;
        break;
// foods
    case "cane":
    case "candy cane":
    case "canes":
    case "candy canes":
        order = clone_object(JOKE_DIR + "cane");
        price = 15;
        break;
    case "sugar cookie":
    case "sugar cookies":
        order = clone_object(JOKE_DIR + "cookie");
        price = 20;
        break;
    case "gingerbread man cookie":
    case "gingerbread man":
    case "gingerbread":
    case "gingerbread man cookies":
    case "gingerbread men":
        order = clone_object(JOKE_DIR + "");
        price = 25;
        break;
    case "pudding":
    case "puddings":
    case "figgy pudding":
    case "figgy puddings":
    case "bowl of pudding":
    case "bowls of pudding":
    case "bowls of figgy pudding":
    case "bowl of figgy pudding":
        order = clone_object(JOKE_DIR + "fpudding");
        price = 45;
        break;
    case "fruit cake":
    case "fruit cakes":
    case "cake":
    case "cakes":
    case "slice of cake":
    case "slices of cake":
    case "slice of fruit cake":
    case "slices of fruitcake":
        order = clone_object(JOKE_DIR + "fruitcake");
        price = 50;
        break;
    case "basket of cookies":
    case "baskets of cookies":
    case "basket of sugar cookies":
    case "baskets of sugar cookies":
        order = clone_object(JOKE_DIR + "cookiebasket");
        price = 740;
        break;
    case "basket of reindeer droppings":
    case "baskets of reindeer droppings":
    case "basket of droppings":
    case "basket of droppings":
        order = clone_object(JOKE_DIR + "dropbasket");
        price = 800;
        break;
    
    }
    return (({order}) + ({price}));
}

