/*
 * Holiday shop for Christmas
 * Modified from the Bree Inn, Only sells things, does not buy anything
 * -- Finwe, November 2001
 */
inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})
#define HOL_DIR "/d/Shire/holidays/"

/* Prototype */
void reset_shire_room();

static object merigrin;

void
create_shire_room()
{
    set_short("The Holiday Shop");
    set_long("You have entered Bree's Holiday Shop. To celebrate " +
        "this time of the year, craftspeople from all over the " +
        "area, both near and far, bring their wares here to be " +
        "sold. Many of the gifts are specially designed with a " +
        "holiday theme. Only items may be purchased here. A sign " +
        "is posted on the wall.\n");
    add_item("sign","The sign has writing on it.\n");
    add_item(({"chair", "chairs"}), "The chairs are made out of wood.\n");
    add_item("counter", "It's made out of wood. There is a man standing "+
      "behind it.\n");
    add_item("walls", 
        "The walls are simple, made of wood with a sign on one.\n");
//    add_item(PRICELIST_ID, "@@pricelist_desc");
    add_item("sign", "Maybe you should read it.\n");
    add_cmd_item("sign", "read", "@@pricelist_desc@@");


// safe rooms
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_exit(BREE_DIR + "townrm","east");

    set_alarm(1.0, 0.0, reset_shire_room);
    configure_shire_inn();
    add_prop(ROOM_I_NO_CLEANUP,1);
}


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
        "\t|    A mistletoe branch. . . .        7 sc  6 cc     |\n"+
        "\t|    A branch of mistletoe used to entice kisses     |\n"+ 
        "\t|                                                    |\n"+
        "\t|    An ivy crown. . . . . . .        8 sc  4 cc     |\n"+
        "\t|    A crown made from woven ivy                     |\n"+
        "\t|                                                    |\n"+
        "\t|    A holiday pinwheel. . . .        8 sc  4 cc     |\n"+
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

void
reset_shire_room()
{
    if (!merigrin)
        merigrin = clone_object(BREE_DIR + "npc/merigrin");
    if (!present(merigrin,this_object()))
        merigrin->move(this_object());

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
    }
    return (({order}) + ({price}));
}

