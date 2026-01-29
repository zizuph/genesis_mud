/*
 * Private common room of the Prancing Pony
 * By Finwe, January 2002
 *
 * Converted over to new Bree
 * -- Finwe, May 2002
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "defs.h"
inherit AREA_ROOM;
inherit "/d/Shire/lib/common_room";

#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})
//#define SUPL_DIR "/d/Shire/common/bree/supplies/"

void create_room()
{
   ::create_room();
    add_prop(ROOM_I_INSIDE, 1);
    set_short("The private dining room of the Prancing Pony");
    set_long("This is the private dining room in the Prancing Pony. Travellers " +
        "come here when they wish for private conversations. It is " +
        "smokey from all the smoked pipeweed, creating a haze that " +
        "hangs over everything. The large room is full of tables, " +
        "some occupied with travellers. The walls are panelled with " +
        "dark wood and have large rectangular windows set into " +
        "them. Curtains hang over the windows, blocking all but " +
        "some small pools of light. Menus sit on each " +
        "table.\n");

    add_item(({"ground", "floor", "down"}),
        "Smooth wood planks make up the bare, clean floor.\n");
    
    add_cmd_item(PRICELIST_ID, "read", "@@menu@@");

    add_exit(TOWN_DIR + "innyard", "north");
 
}

int
menu(string str)
{

    write(
        "\t       The Prancing Pony Private Dining Room Menu\n"+
        "\t.------------------------------------------------------.\n" +
        "\t| +                                                  + |\n" +
        "\t|                                                      |\n" +
        "\t|   1. Coffee. . . . . . . . . . .        3 sc  4 cc   |\n" +
        "\t|   2. Green tea . . . . . . . . .        1 sc  8 cc   |\n" +
        "\t|   3. Black tea . . . . . . . . .        1 sc  8 cc   |\n" +
        "\t|   4. Mulled ale. . . . . . . . .        6 sc  3 cc   |\n" +
        "\t|   5. Vegetable pie . . . . . . .  1 gc  0 sc  6 cc   |\n" +
        "\t|   6. Meat pie. . . . . . . . . .  1 gc  0 sc  6 sc   |\n" +
        "\t|   7. Sauteed potatoes. . . . . .        6 sc  5 sc   |\n" +
        "\t|   8. Roasted wild boar . . . . .  1 gc  1 sc  4 cc   |\n" +
        "\t|   9. Steamed mushrooms . . . . .       11 sc  0 cc   |\n" +
        "\t|  10. Roasted game hen. . . . . .  1 gc  2 sc  7 c    |\n" +
        "\t|                                                      |\n" +
        "\t| +                                                  + |\n" +
        "\t`------------------------------------------------------'\n\n");
    return 1;
}


// shows how to add foods and drinks to inn

int
do_order(string str) 
{
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
    case "coffee":
    case "coffees":
    case "1":
        order = clone_object(FOOD_DIR + "coffee");
        price = 40;
        break;
    case "green tea":
    case "green teas":
    case "2":
        order = clone_object(FOOD_DIR + "g_tea");
        price = 20;
        break;
    case "black tea":
    case "black teas":
    case "3":
        order = clone_object(FOOD_DIR + "b_tea");
        price = 20;
        break;
    case "ale":
    case "mulled ale":
    case "mulled ales":
    case "ales":
    case "4":
        order = clone_object(FOOD_DIR + "ale");
        price = 75;
        break;
    case "vegetable pie":
    case "vegetable pies":
    case "5":
        order = clone_object(FOOD_DIR + "pie_veg");
        price = 150;
        break;

    case "meat pie":
    case "meat pies":
    case "6":
        order = clone_object(FOOD_DIR + "pie_meat");
        price = 150;
        break;

    case "potatoes":
    case "sauteed potatoes":
    case "7":
        order = clone_object(FOOD_DIR + "potatoes");
        price = 77;
        break;
    case "boar":
    case "wild boar":
    case "boars":
    case "wild boars":
    case "roasted boar":
    case "roasted wild boar":
    case "roasted boars":
    case "roasted wild boars":
    case "8":
        order = clone_object(FOOD_DIR + "boar");
        price = 160;
        break;
    case "mushrooms":
    case "steamed mushrooms":
    case "9":
        order = clone_object(FOOD_DIR + "mushrooms");
        price = 132;
        break;
    case "hens":
    case "hen":
    case "game hen":
    case "roasted game hen":
    case "roasted game hens":
    case "game hens":
    case "10":
        order = clone_object(FOOD_DIR + "hen");
        price = 175;
        break;

    }
    return (({order}) + ({price}));
}
