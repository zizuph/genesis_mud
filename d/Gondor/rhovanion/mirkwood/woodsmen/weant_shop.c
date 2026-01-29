/*
 * Weanting
 * Varian - March 2015
 */

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit MIRKWOOD_STD_DIR + "room";
inherit "/lib/shop.c";
inherit "/d/Emerald/lib/shop_list";

static object shopkeeper;

void
create_mirkwood_room()
{
    set_short("General store in Weanting");
    add_long("You are standing in the middle of the general store for the " +
        "village of Weanting. The walls are all lined with shelves, filled " +
        "with a wide variety of useful goods, while a small counter at the " +
        "north end of the building appears to function as a sales desk. " +
        "A large poster hangs on the wall behind the counter, providing " +
        "some instructions for any customers who wish to make a purchase " +
        "here. A narrow opening has been curtained off along the west " +
        "wall, while both the door and the windows in the southern wall " +
        "look out into the village outside.", LIGHT_ALL);
  
    add_item_light(({"store", "general store", "room"}),
        "You are standing in the middle of the general store for the " +
        "village of Weanting. The walls are all lined with shelves, filled " +
        "with a wide variety of useful goods, while a small counter at the " +
        "north end of the building appears to function as a sales desk. " +
        "A large poster hangs on the wall behind the counter, providing " +
        "some instructions for any customers who wish to make a purchase " +
        "here. A narrow opening has been curtained off along the west " +
        "wall, while both the door and the windows in the southern wall " +
        "look out into the village outside.\n", LIGHT_ALL);
    add_item_light(({"shelf", "shelves", "wooden shelf", "wooden shelves"}),
        "The walls inside the general store are lined with plenty of solid, " +
        "wooden shelves, all of which are filled with all sorts of useful " +
        "goods. If you would like to purchase anything from the shelves, " +
        "perhaps you should read the poster for further instructions.\n", LIGHT_ALL);
    add_item_light(({"goods", "useful goods"}),
        "There are plenty of interesting items here for sale, many of them " +
        "quite useful for anyone who travels around the world. You can read " +
        "the poster here to get a better idea of how you can sort through " +
        "these goods.\n", LIGHT_ALL);
    add_item_light(({"counter", "desk", "north wall", "sales desk", "wooden counter"}),
        "This is a simple wooden counter which sits in front of the north wall of " +
        "the store. The counter is not very large, but it is big enough to serve " +
        "in its function of providing the shopkeeper a place to conduct his sales.\n", LIGHT_ALL);
    add_item_light(({"poster", "sign"}),
        "This poster offers some useful information about how you can purchase " +
        "goods in this store. Perhaps you should read it?\n", LIGHT_ALL);
    add_item_light(({"opening", "west wall", "curtain"}),
        "Along the west wall, you notice a narrow opening with a dark curtain " +
        "hanging over it. This appears to be the back room where the storekeeper " +
        "keeps most of his stock. If it was not already obvious, you are not " +
        "permitted to go back there.\n", LIGHT_ALL);
    add_item_light(({"door", "wooden door", "south wall"}),
        "This wooden door leads back out into the village of Weanting.\n", LIGHT_ALL);
    add_item_light(({"windows", "window"}),
        "There are several small windows in the southern wall, all of which " +
        "offer a glimpse out into the village of Weanting.\n", LIGHT_ALL);
    add_item_light(({"wall", "walls"}),
        "Which wall did you wish to examine?\n", LIGHT_ALL);
    add_item_light(({"floor", "planks", "wooden planks"}),
        "The floor of the store has been constructed with wide wooden planks " +
        "which are rather plain and look to have only been roughly planed " +
        "and sanded. The floor is both rather servicable and unremarkable.\n", LIGHT_ALL);
    add_item_light(({"east wall", "bin", "bins"}),
        "The east wall of the store is filled with several wooden shelves in " +
        "addition to a couple of wooden bins which are also filled with " +
        "goods for sale.\n", LIGHT_ALL);
    add_item_light(({"ceiling", "beam", "beams", "wooden beams", "wooden beam"}),
        "The ceiling of the general store is of fairly simple construction, with " +
        "several wooden beams spanning the distance between the walls.\n", LIGHT_ALL);

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT, LIGHT_BRIGHT);

    reset_room();

    config_default_trade();
    set_money_give_max(1000);
    set_store_room(WOODSMEN_DIR + "weant_shop2");
    
    add_exit(WOODSMEN_DIR + "weanting2", "south", "@@village@@");
    add_exit(WOODSMEN_DIR + "weant_shop2", "west", "@@shop@@");
}

int
village()
{
    write("\n\nYou make your way back out into the village of Weanting.\n\n");
    return 0;
}

int
shop()
{
    write("You attempt to enter the narrow opening in the west wall " +
        "but the shopkeeper stops you.\n");
    return 1;
}

void
init()
{
    ::init();
    init_shop();
    add_action("do_read","read");
}

int
do_read(string str)
{
    if(!str)
    {
        notify_fail("Read what? The poster?\n");
        return 0;
    }
    if((str != "sign") && (str != "poster"))
    { 
        notify_fail("Read what? The poster?\n");
        return 0;
    }

    write("You can try these instructions: \n" +
        "buy sword for gold coins    (default: the smallest denomination)\n" +
        "buy sword for gold and get copper back\n" +
        "sell sword for copper coins (default: the largest denomination)\n" +
        "sell all  - will let you sell all items except for items you wield\n" +
        "            or wear. Beware that if you have many items to sell,\n" +
        "            check whether you have sold all or repeat the command.\n" +
        "sell all! - will let you sell ALL items you have, well at least the\n" +
        "            droppable ones, and no coins. (see warning at 'sell all')\n" +
        "sell sword, sell second sword, sell sword 2, sell two swords also\n" +
        "            works. Beware, you will never buy more than one item at\n" +
        "            a time. So if you really those three expensive swords, you\n" +
        "            have to repeat yourself three times.\n" +
        "value     - will value an item you carry before you decide to sell it.\n" +
        "show      - appraise one of the items in stock before you buy it.\n" +
        "list      - will list the items in stock, 'list armour' and 'list\n" +
        "            weapon' are valid commands, or e.g. 'list sword'.\n" +
        "            multiple types can be listed as well, e.g. 'list axe,\n" +
        "            helmet, general'.\n" +
        "mlist     - the same as 'list', but using 'more'.\n");
    SAYBB(" goes up near the counter to read the poster on the wall.");
    return 1;
}

void
shop_hook_list_object(object ob, int price)
{
    string str, mess, categ;

    str = sprintf("%-41s", capitalize(LANG_ASHORT(ob)));
    categ = figure_category(ob);
    if (mess = text(split_values(price)))
    {
        mess = sprintf(" %-8s | %2d %2d %2d %2d", categ, price / 1728, (price 
            % 1728) / 144, (price % 144) / 12, price % 12);
        write("| " +str + "|" + mess + " |\n");
    }
    else
    {
        write(str + "That item wouldn't cost you much.\n");
    }

}

void
reset_room() 
{
    ::reset_room();

    if(!shopkeeper) shopkeeper = clone_object(WOODSMEN_DIR + "npc/athling.c");
    if (!present(shopkeeper)) shopkeeper->move_living("somewhere", this_object());
}

void
remove_object()
{
    shopkeeper->remove_object();
    ::remove_object();
}
