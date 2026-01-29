/*
 * Easter shop
 *  * -- Finwe, April 2007
 */
#include "/d/Faerun/defs.h"
#include <filter_funs.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

inherit FAERUN_OUTDOOR_BASE;
inherit "/d/Faerun/lib/inn";

#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})
#define EASTER_DIR      "/d/Faerun/holidays/easter/"

/* Prototype */

static object alethra;
void reset_room();


void
create_faerun_room()
{
    set_short("The Festival Shop of Faerun");
    set_long("This is Festival Shop of Faerun. It is bright and full of items made by various craftspeople of the area. The items are specially designed for this time of the year and are only for sale for a limited time. A sign is posted on a wall above a wooden counter.\n");

    add_item("counter", 
        "It's made out of wood and stretches the width of the room.\n");
    add_item("walls",
        "The walls are simple. They are made of wood and have with a " +
        "sign posted on one.\n");
    add_item(({"sign", "poster", "menu"}), "There is some writing on it. Maybe " +
        "you should read it.\n");
    add_cmd_item("sign", "read", "@@pricelist_desc@@");


    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_exit("/d/Faerun/common/domain_office", "south");

    configure_shire_inn();
    add_prop(ROOM_I_NO_CLEANUP,0);
    reset_room();
}

void
reset_room()
{
    if (!alethra)
    {
        alethra = clone_object(EASTER_DIR + "alethra");
        alethra->move(this_object());
    }

}

// Sign
string
pricelist_desc()
{
    return "\n"+
        "\t+------------------------------------------------------+\n"+
        "\t|                                                      |\n"+
        "\t|   *                                              *   |\n"+
        "\t|                  Faerun Holiday Shop                 |\n"+
        "\t|                                                      |\n"+
        "\t|     Below are the items available here. They are     |\n"+
        "\t|     crafted from the best materials available. Eggs  |\n"+
        "\t|     purchased here will not work with any events.    |\n"+
        "\t|                                                      |\n"+
        "\t|     Food                                             |\n"+
        "\t|     ---------------------------------------------    |\n"+
        "\t|     Jelly Bean . . . . . . . .               5 cc    |\n"+
        "\t|     Pouch of Jelly Beans . . .   4 gc  6 sc  0 cc    |\n"+ // 648 cc
        "\t|     Marshmallow Peep . . . . .         1 sc  0 cc    |\n"+ // 12 cc
        "\t|     Chocolate Egg. . . . . . .         3 sc  0 cc    |\n"+ // 36 cc
        "\t|     Chocolate Figurine . . . .         6 sc  0 cc    |\n"+ // 72 cc
        "\t|                                                      |\n"+
        "\t|     Miscellaneous Items                              |\n"+
        "\t|     ---------------------------------------------    |\n"+
        "\t|     Easter Egg . . . . . . . .         2 sc  0 cc    |\n"+ // 12 cc
        "\t|     Easter Basket with Eggs. .   2 gc  6 sc  0 cc    |\n"+ // 360 cc
        "\t|     Plush Easter Bunny . . . .  12 gc  0 sc  0 cc    |\n"+ //1728 cc  
        "\t|     Plush Easter Chick . . . .   6 gc  0 sc  0 sc    |\n"+ // 864 cc
        "\t|                                                      |\n"+
        "\t|     Easter eggs may be any of the following colors:  |\n"+
        "\t|     red, yellow, green, brown, scarlet, black,       |\n"+
        "\t|     ocher, peach, ruby, olive, violet, fawn, lilac,  |\n"+
        "\t|     gold, chocolate, mauve, cream, crimson, silver,  |\n"+
        "\t|     rose, azure, lemon, russet, grey, purple, white, |\n"+
        "\t|     pink, orange, and blue!                          |\n"+
        "\t|                                                      |\n"+
        "\t|     Jelly beans may be any of the following colors   |\n"+
        "\t|     and flavors:                                     |\n"+
        "\t|     red as strawberry, yellow as lemon, green as     |\n"+
        "\t|     lime, brown as chocolate, scarlett as cherry,    |\n"+
        "\t|     black as licorace, ruby as raspberry, dark-red   |\n"+
        "\t|     as tropical punch, cream as coconut, crimson as  |\n"+
        "\t|     cinnamon, purple as grape, white as pineapple,   |\n"+
        "\t|     pink as pink lemonade, orange as orange, blue    |\n"+
        "\t|     as blueberry, light-orange as cantalope,         |\n"+
        "\t|     lavendar as plum.                                |\n"+
        "\t|                                                      |\n"+
        "\t|     The chocolate figurines may come in the follow-  |\n"+
        "\t|     ing shapes:                                      |\n"+
        "\t|     bear, bunny, cat, dog, dwarf, elf, frog, gnome,  |\n"+
        "\t|     goblin, lion, minotaur, moose, mouse, ogre,      |\n"+
        "\t|     pig, rabbit, rat, sheep, squirrel, and a wolf.   |\n"+
        "\t|                                                      |\n"+
        "\t|     They come in following types of chocolate:       |\n"+
        "\t|     white, milk, dark, sweet dark, and bittersweet.  |\n"+
        "\t|                                                      |\n"+
        "\t|   *                                              *   |\n"+
        "\t|                                                      |\n"+
        "\t+------------------------------------------------------+\n\n";
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
    if (!alethra || !present(alethra))
    {
        notify_fail("There is no one here to buy anything from. " +
          "The shopkeeper has left to get more supplies.\n");
        return 0;
    }

    log_file("sales", extract(ctime(time()), 4,15) + " " + CAP(TP->query_real_name())+ "  " + "(" + TP->query_average_stat() + ") bought " + str + ".\n");
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
    case "bean":
    case "jelly bean":
    case "beans":
    case "jelly beans":
        order = clone_object(EASTER_DIR + "jbean2");
        price = 5;
        break;
    case "pouch":
    case "pouches":
    case "pouch of jelly bean":
    case "pouches of jelly beans":
        order = clone_object(EASTER_DIR + "pouch");
        price = 648;
        break;
    case "peep":
    case "peeps":
    case "marshmallow peep":
    case "marshmallow peeps":
        order = clone_object(EASTER_DIR + "peep");
        price = 12;
        break;
    case "chocolate egg":
    case "chocolate eggs":
        order = clone_object(EASTER_DIR + "choc_egg");
        price = 36;
        break;
    case "figurine":
    case "figurines":
    case "chocolate figurine":
    case "chocolate figurines":
        order = clone_object(EASTER_DIR + "choco_animal");
        price = 72;
        break;
    case "easter egg":
    case "easter eggs":
        order = clone_object(EASTER_DIR + "egg");
        price = 12;
        break;
    case "basket":
    case "baskets":
    case "easter basket":
    case "easter baskets":
        order = clone_object(EASTER_DIR + "basket_egg");
        price = 360;
        break;
    case "bunny":
    case "bunnys":
    case "bunnies":
    case "easter bunny":
    case "easter bunnies":
    case "easter bunnys":
        order = clone_object(EASTER_DIR + "plush_bunny");
        price = 1728;
        break;
    case "chick":
    case "chicks":
    case "easter chick":
    case "easter chicks":
        order = clone_object(EASTER_DIR + "plush_chick");
        price = 864;
        break;
    }
    return (({order}) + ({price}));
}

