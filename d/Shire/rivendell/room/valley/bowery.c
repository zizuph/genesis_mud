/*
 * Bowery for Imladris
 * Modified from the Bree Inn, Only sells things, does not buy anything
 * -- Finwe, June 2004
 */
inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";

#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define PRICELIST_ID  ({"pricelist","list","prices"})

/* Prototype */
void reset_shire_room();

static object falendil;

void
create_shire_room()
{
    set_short("The Bowery of Imladris");
    set_long("The Bowery of Imladris. This large shop is where elves " +
        "who are preparing to protect the lands visit. Expertly made " +
        "bows and arrows may be purchased here. A sign is posted on " +
        "a wall.\n");
    add_item("counter", "It's made out of wood. There is a man standing "+
      "behind it.\n");
    add_item("walls", 
        "The walls are simple, made of wood with a sign on one.\n");
//    add_item(PRICELIST_ID, "@@pricelist_desc");
    add_item(({"sign", "poster"}), "There is some writing on it. Maybe " +
        "you should read it.\n");
    add_cmd_item("sign", "read", "@@pricelist_desc@@");
    add_cmd_item(({"poster", "sign"}), "read", "@@poster_desc@@");


    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

    set_alarm(1.0, 0.0, reset_shire_room);
    configure_shire_inn();
    add_prop(ROOM_I_NO_CLEANUP,1);
    add_exit(VALLEY_DIR + "n_path03", "east");
    reset_shire_room();

}

// Sign
string
pricelist_desc()
{
    return "\n"+
        "\t+----------------------------------------------------+\n"+
        "\t|                                                    |\n"+
        "\t|                  Imladris Bowery                   |\n"+
        "\t|                                                    |\n"+
        "\t|    Bows are often the weapon of choice for elves.  |\n"+
        "\t|    Their expert craftsmanship is now available     |\n"+
        "\t|    to those who aid them in defending their land.  |\n"+
        "\t|    You may purchase any of the items below.        |\n"+
        "\t|                                                    |\n"+
        "\t|    A leather quiver. . . . . . . .  8 sc  4 cc     |\n"+
        "\t|    A plain leather quiver to hold arrows           |\n"+ 
        "\t|                                                    |\n"+
        "\t|    A steel quiver. . . . . .  1 gc  4 sc  8 cc     |\n"+
        "\t|    A decorated steel quiver to hold arrows         |\n"+
        "\t|                                                    |\n"+
        "\t|    A wooden arrow. . . . . . . . .  7 sc  0 cc     |\n"+
        "\t|    An expertly crafted wooden arrow                |\n"+
        "\t|                                                    |\n"+
        "\t|    A bow string. . . . . . . . . .  4 sc  2 cc     |\n"+
        "\t|    A string to replace broken bow strings          |\n"+
        "\t|                                                    |\n"+
        "\t|    A steel bow . . . . . . . 10 gc  5 sc  0 cc     |\n"+
        "\t|    An expert bow made by the Noldor                |\n"+
        "\t|                                                    |\n"+
        "\t|                                                    |\n"+
        "\t+----------------------------------------------------+\n\n";
}


void
reset_shire_room()
{
    if (!falendil)
        falendil = clone_object(RNPC_DIR + "falendil");
    if (!present(falendil,this_object()))
        falendil->move(this_object());

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
    if (!falendil || !present(falendil))
    {
        notify_fail("The fletcher is gone. He should return shortly.\n");
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
    case "leather quiver":
    case "leather quivers":
        order = clone_object(ROBJ_DIR + "quiver_l");
        price = 100;
        break;
    case "steel quiver":
    case "steel quivers":
        order = clone_object(ROBJ_DIR + "quiver_s");
        price = 200;
        break;
    case "arrow":
    case "arrows":
    case "wooden arrows":
    case "wooden arrow":
        order = clone_object(RWEP_DIR + "arrows");
        price = 84;
        break;
    case "string":
    case "strings":
    case "bow string":
    case "bow strings":
        order = clone_object(ROBJ_DIR + "bowstring");
        price = 50;
        break;
    case "bow":
    case "bows":
    case "steel bow":
    case "steel bows":
    case "light bow":
    case "light bows":
    case "light steel bow":
    case "light steel bows":
        order = clone_object(RWEP_DIR + "bow");
        price = 1500;
        break;

    }
    return (({order}) + ({price}));
}

