/*
 * Holiday shop for Christmas
 * Modified from the Bree Inn, Only sells things, does not buy anything
 * -- Finwe, November 2001
 */
inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";

#include "/d/Shire/sys/defs.h"
#include "defs.h"

#include <filter_funs.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})
#define HOL_DIR "/d/Shire/holidays/xmas/"
#define HOLIDAY_SALES (HOL_DIR + "holiday_sales.log")

/* Prototype */
void reset_shire_room();

static object merigrin;

void
create_shire_room()
{
    set_short("The Holiday Shop");
    set_long("You have entered Bree's Holiday Shop. To celebrate " +
        "this time of the year, craftspeople and bakers from all over the " +
        "area, both near and far, bring their wares here to be " +
        "sold. The gifts, food, and drinks are specially designed with a " +
        "holiday theme. Only items may be purchased here. A sign " +
        "is posted on one wall, and a menu on another.\n");
    add_item(({"chair", "chairs"}), "The chairs are made out of wood.\n");
    add_item("counter", "It's made out of wood and stretches the width " +
        "of the room.\n");
    add_item("walls", 
        "The walls are simple. They are made of wood and have with a " +
        "sign on one and a poster on another.\n");
//    add_item(PRICELIST_ID, "@@pricelist_desc");
    add_item(({"sign", "poster", "menu"}), "There is some writing on it. Maybe " +
        "you should read it.\n");
    add_cmd_item("sign", "read", "@@pricelist_desc@@");
    add_cmd_item(({"menu"}), "read", "@@poster_desc@@");


    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_exit(ROAD_DIR + "broad03","north");

    set_alarm(1.0, 0.0, reset_shire_room);
    configure_shire_inn();
    add_prop(ROOM_I_NO_CLEANUP,0);
}

// Sign
string
pricelist_desc()
{
    return "\n"+
        "\t+----------------------------------------------------+\n"+
        "\t|                                                    |\n"+
        "\t|   *                                            *   |\n"+
        "\t|                 Bree Holiday Shop                  |\n"+
        "\t|                                                    |\n"+
        "\t|    Below are the items sold here. Items cannot be  |\n"+
        "\t|    returned or sold back here                      |\n"+
        "\t|                                                    |\n"+
        "\t|    A mistletoe branch . . . .       7 sc  6 cc     |\n"+
        "\t|    A branch of mistletoe used to entice kisses     |\n"+ 
        "\t|                                                    |\n"+
        "\t|    An ivy crown . . . . . . .       8 sc  4 cc     |\n"+
        "\t|    A crown made from woven ivy                     |\n"+
        "\t|                                                    |\n"+
        "\t|    A holiday pinwheel . . . .       8 sc  4 cc     |\n"+
        "\t|    A cute snowflake pinwheel fun to play with      |\n"+
        "\t|                                                    |\n"+
        "\t|    A festive sash . . . . . . 2 gc                 |\n"+
        "\t|    A colorful sash embroidered holly branches      |\n"+
        "\t|                                                    |\n"+
        "\t|    A water globe. . . . . . . 2 gc  9 sc  4 cc     |\n"+
        "\t|    A crystal globe with a village scene inside     |\n"+
        "\t|                                                    |\n"+
        "\t|    A white cloak. . . . . . . 3 gc  1 sc  6 cc     |\n"+
        "\t|    A white cloak embroidered with snowflakes       |\n"+
        "\t|                                                    |\n"+
        "\t|   *                                            *   |\n"+
        "\t|                                                    |\n"+
        "\t+----------------------------------------------------+\n\n";
}


// Poster 
string
poster_desc()
{
    return "\n"+
        "\t+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n"+
        "\t|                                                    |\n"+
        "\t|   O                                            O   |\n"+
        "\t|                 Bree Holiday Foods                 |\n"+
        "\t|                                                    |\n"+
        "\t|    Listed below are the various foods and drinks   |\n"+
        "\t|    available for sale here.                        |\n"+
        "\t|                                                    |\n"+
        "\t|    Drinks                           gc   sc   cc   |\n"+
        "\t|    ----------------------------------------------  |\n"+
        "\t|    A mug of eggnog. . . . . . . . .      1s   8c   |\n"+
        "\t|    A mug of hot chocolate . . . . .      2s   6c   |\n"+
        "\t|    A mug of spiced cider. . . . . .      2s   6c   |\n"+
        "\t|    A glass of mulled wine . . . . .      3s   4c   |\n"+
        "\t|    A mug of wassail . . . . . . . .      4s   2c   |\n"+
        "\t|    A mug of glogg . . . . . . . . .      5s   5c   |\n"+
        "\t|                                                    |\n"+
        "\t|    Foods                            gc   sc   cc   |\n"+
        "\t|    ----------------------------------------------  |\n"+
        "\t|    A candy cane . . . . . . . . . .      1s   3c   |\n"+
        "\t|    A sugar cookie . . . . . . . . .      1s   8c   |\n"+
        "\t|    A gingerbread man cookie . . . .      2s   1c   |\n"+
        "\t|    A bowl of figgy pudding. . . . .      3s   9c   |\n"+
        "\t|    A slice of fruit cake. . . . . .      4s   4c   |\n"+
        "\t|    A basket of sugar cookies. . . . 5g   1s   8c   |\n"+
//        "\t|    A basket of reindeer droppings . 5g   6s   8c   |\n"+
//        "\t|    A basket of frangos. . . . . . . 6g             |\n"+
        "\t|                                                    |\n"+
        "\t|   O                                            O   |\n"+
        "\t|                                                    |\n"+
        "\t+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n\n";
}


void
reset_shire_room()
{
    if (!merigrin)
    {
        merigrin = clone_object(NPC_DIR + "merigrin");
        merigrin->move(this_object());
    }

}

void
init()
{
    ::init();
    init_shire_inn();
//    add_action("do_read", "read", 0);
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
    if (!merigrin || !present(merigrin))
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
        order = clone_object(HOL_DIR + "wcloak");
        price = 450;
        break;
    case "globe":
    case "water globe":
    case "water globes":
    case "globes":
        order = clone_object(HOL_DIR + "water_globe");
        price = 400;
        break;
    case "pinwheel":
    case "pinwheels":
    case "holiday pinwheel":
    case "holiday pinwheels":
        order = clone_object(HOL_DIR + "pinwheel");
        price = 100;
        break;
    case "mistletoe":
    case "mistletoes":
    case "branch":
    case "branches":
    case "mistletoe branch":
    case "mistletoe branches":
        order = clone_object(HOL_DIR + "mistletoe");
        price = 90;
        break;
    case "sash":
    case "festive sash":
    case "sashs":
    case "festive sashes":
        order = clone_object(HOL_DIR + "sash");
        price = 288;
        break;
    case "crown":
    case "crowns":
    case "ivy crown":
    case "ivy crowns":
        order = clone_object(HOL_DIR + "crown");
        price = 100;
        break;
// drinks
    case "eggnog":
    case "mug of eggnog":
    case "eggnogs":
    case "mugs of eggnog":
        order = clone_object(HOL_DIR + "eggnog");
        price = 20;
        break;
    case "hot chocolate":
    case "hot chocolates":
    case "mug of hot chocolate":
    case "mugs of hot chocolates":
        order = clone_object(HOL_DIR + "hotchoc");
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
        order = clone_object(HOL_DIR + "cider");
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
        order = clone_object(HOL_DIR + "mwine");
        price = 40;
        break;
    case "wassail":
    case "wassails":
    case "mug of wassail":
    case "mugs of wassail":
        order = clone_object(HOL_DIR + "wassail");
        price = 50;
        break;
    case "glogg":
    case "gloggs":
    case "mug of glogg":
    case "mugs of glogg":
        order = clone_object(HOL_DIR + "glogg");
        price = 65;
        break;
// foods
    case "cane":
    case "candy cane":
    case "canes":
    case "candy canes":
        order = clone_object(HOL_DIR + "cane");
        price = 15;
        break;
    case "sugar cookie":
    case "sugar cookies":
        order = clone_object(HOL_DIR + "cookie");
        price = 20;
        break;
    case "gingerbread man cookie":
    case "gingerbread man":
    case "gingerbread":
    case "gingerbread man cookies":
    case "gingerbread men":
        order = clone_object(HOL_DIR + "gingerbread");
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
        order = clone_object(HOL_DIR + "fpudding");
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
        order = clone_object(HOL_DIR + "fruitcake");
        price = 50;
        break;
    case "basket of cookies":
    case "baskets of cookies":
    case "basket of sugar cookies":
    case "baskets of sugar cookies":
        order = clone_object(HOL_DIR + "cookiebasket");
        price = 740;
        break;
/*
    case "basket of reindeer droppings":
    case "baskets of reindeer droppings":
    case "basket of droppings":
    case "basket of droppings":
        order = clone_object(HOL_DIR + "dropbasket");
        price = 800;
        break;
    case "basket of frangos":
    case "baskets of frangos":
    case "frangos":
        order = clone_object(HOL_DIR + "frangobasket");
        price = 864;
        break;
*/
    }

    write_file(HOLIDAY_SALES, TP->query_name()+" bought " + item_name + " for " + price + " coppers.\n");
    return (({order}) + ({price}));
}

