/*
 * Inn for Longbottom
 * Finwe, January 2020
 */

inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/inn";

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})

/* Prototype */
void reset_shire_room();

static object innkeeper;

void
create_shire_room()
{
    set_short("The Silver Tree Inn");
    set_long("This is the Silver Tree Inn in Longbottom. Townsfolk gather " +
        "here to discuss " +
        "the happenings of the town and hear the news of the world. A " +
        "wooden counter runs the length of the inn, and a menu hangs " +
        "above the counter. Tables and chairs are spread around the " +
        "room. Smoke hangs like a curtain near the ceiling.\n");

    add_item("menu","The menu has writing on it.\n");
    add_item(({"chair", "chairs"}), "The chairs are made out of wood. " +
        "They are set around the tables.\n");
    add_item(({"table", "tables"}),
        "They are round and made of wood. They tables are surrounded with " +
        "chairs and polished clean.\n");
    add_item("counter", "It's made out of wood. It runs the length of " +
        "the inn and is polished clean.\n");

    add_item(PRICELIST_ID, "@@pricelist_desc");

// safe rooms
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_exit(LB_RM_DIR + "lb01","southwest");

    set_alarm(1.0, 0.0, reset_shire_room);
    configure_shire_inn();
    add_prop(ROOM_I_NO_CLEANUP,1);
}

string
pricelist_desc()
{
    return "" +
    "\t    _                                              _\n" +
    "\t __| |____________________________________________| |__\n" +
    "\t(__ + ____________________________________________ + __)\n" +
    "\t   | |                                            | |\n" +
    "\t   | |            The Silver Tree Inn             | |\n" +
    "\t   | |                                            | |\n" +
    "\t   | |  Drinks:                                   | |\n" +
    "\t   | |    A glass of water. . . . . . . . . 6 cc  | |\n" +
    "\t   | |    A glass of beer . . . . . . . . . 2 sc  | |\n" +
    "\t   | |    A pint of ale . . . . . . . . . . 4 sc  | |\n" +
    "\t   | |    A glass of red wine . . . . . . . 8 sc  | |\n" +
    "\t   | |    A glass of whiskey. . . . . . . . 7 sc  | |\n" +
    "\t   | |                                            | |\n" +
    "\t   | |  Snacks:                                   | |\n" +
    "\t   | |    A slice of bread. . . . . . . . . 1 sc  | |\n" +
    "\t   | |    Potato wedges . . . . . . . . . . 4 sc  | |\n" +
    "\t   | |    Chicken strips. . . . . . . . . . 4 sc  | |\n" +
    "\t   | |                                            | |\n" +
    "\t   | |  Meals:                                    | |\n" +
    "\t   | |    Fish chowder. . . . . . . . . . . 6 sc  | |\n" +
    "\t   | |    BLT sandwich. . . . . . . . . . . 7 sc  | |\n" +
    "\t   | |    Plate of grilled sausage. . . . . 9 sc  | |\n" +
    "\t   | |                                            | |\n" +
    "\t   | |  You may order for other players or order  | |\n" +
    "\t   | |  for multiple players.                     | |\n" +
    "\t   | |                                            | |\n" +
    "\t   | |  Try using 'order <item> for players',     | |\n" +
    "\t   | |  like when you target players with an      | |\n" +
    "\t   | |  emotion.                                  | |\n" +
    "\t   | |                                            | |\n" +
    "\t   | |  You can also 'order <item> for team' to   | |\n" +
    "\t   | |  order food and drinks for your teammates. | |\n" +
    "\t __| |____________________________________________| |__\n" +
    "\t(__ + ____________________________________________ + __)\n" +
    "\t   |_|                                            |_|\n\n";

}

void
reset_shire_room()
{
    if (!innkeeper)
        innkeeper = clone_object(LB_NPC_DIR + "innkeeper");

    if (!present(innkeeper,this_object()))
        innkeeper->move(this_object());
}

void
init()
{
    ::init();
    init_shire_inn();
    add_action("do_read", "read", 0);
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

    if (!innkeeper || !present(innkeeper))
    {
        notify_fail("The innkeeper is gone for now, but will return " +
        "shortly, so you are unable to buy anything\n");
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
    case "water":
    case "waters":
    case "glass of water":
    case "glasses of water":
        order = clone_object(LB_FOOD_DIR + "water");
        price = 6;
        break;
    case "beer":
    case "cold beer":
    case "beers":
    case "cold beers":
        order = clone_object(LB_FOOD_DIR + "beer");
        price = 24;
        break;
    case "ale":
    case "pint":
    case "pint of ale":
    case "ales":
    case "pints":
    case "pints of ale":
        order = clone_object(LB_FOOD_DIR + "ale");
        price = 48;
        break;
    case "wine":
    case "red wine":
    case "glass of wine":
    case "wines":
    case "red wines":
    case "glasses of wine":
        order = clone_object(LB_FOOD_DIR + "red_wine");
        price = 96;
        break;
    case "whiskey":
    case "glass of whiskey":
    case "whiskeys":
    case "whiskies":
    case "glasses of whiskey":
    case "glasses of whiskies":
    case "whisky":
    case "glass of whisky":
    case "whiskys":
    case "glasses of whisky":
    case "glasses of whiskys":

        order = clone_object(LB_FOOD_DIR + "whiskey");
        price = 84;
        break;
    case "bread":
    case "breads":
    case "slice of bread":
    case "slices of bread":
        order = clone_object(LB_FOOD_DIR + "bread");
        price = 12;
        break;
    case "wedges":
    case "wedge":
    case "potato wedges":
    case "potato wedge":
        order = clone_object(LB_FOOD_DIR + "potato_wedges");
        price = 48;
        break;
    case "strips":
    case "strip":
    case "chicken strips":
    case "chicken strip":
        order = clone_object(LB_FOOD_DIR + "chicken_strips");
        price = 48;
        break;
    case "chowder":
    case "chowders":
    case "fish chowder":
    case "fish chowders":
        order = clone_object(LB_FOOD_DIR + "fish_chowder");
        price = 72;
        break;
    case "blt":
    case "blt sandwich":
    case "blt sandwiches":
    case "sandwich":
    case "sandwiches":
    case "sandwichs":
    case "blts":
    case "BLT":
    case "BLTs":
    case "BLTS":

        order = clone_object(LB_FOOD_DIR + "blt_sandw");
        price = 84;
        break;
    case "sausages":
    case "sausage":
    case "grilled sausage":
    case "grilled sausages":
    case "plate of grilled sausage":
    case "plate of grilled sausages":
        order = clone_object(LB_FOOD_DIR + "sausage");
        price = 108;
        break;
    }

    return (({order}) + ({price}));
}


int
block_room()
{
    if (this_player()->query_wiz_level()) return 0;

        write("You cannot go there yet.\n");
    return 1;
}
