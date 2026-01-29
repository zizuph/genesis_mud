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
    set_short("Urguk's Sundries and Stuff");
    add_long("A large banner across the south wall of this store proclaims " +
        "it to be the famous 'Urguk's Sundries and Stuff'. Rumoured to be " +
        "a primary supplier of food and goods to the Great Goblin and his " +
        "people in Goblin-town, Urguk is believed to be the wealthiest " +
        "goblin in Mirkwood, if not all of Middle-Earth. Hundreds of boxes, " +
        "barrels, shelves and crates have been neatly packed and organized " +
        "inside this store, ready to serve potential customers in the best " +
        "manner possible. An ornate wooden counter runs along the length " +
        "of the east wall, providing customers a place to put their " +
        "desired goods as they pay. In the middle of the western wall, a " +
        "wide opening has been covered by a curtain while a stout wooden " +
        "door in the north wall leads back out into the " +
        "village of Hargnak. \n", LIGHT_ALL);
  
    add_item_light(({"store","room"}),
        "A large banner across the south wall of this store proclaims " +
        "it to be the famous 'Urguk's Sundries and Stuff'. Rumoured to be " +
        "a primary supplier of food and goods to the Great Goblin and his " +
        "people in Goblin-town, Urguk is believed to be the wealthiest " +
        "goblin in Mirkwood, if not all of Middle-Earth. Hundreds of boxes, " +
        "barrels, shelves and crates have been neatly packed and organized " +
        "inside this store, ready to serve potential customers in the best " +
        "manner possible. An ornate wooden counter runs along the length " +
        "of the east wall, providing customers a place to put their " +
        "desired goods as they pay. In the middle of the western wall, a " +
        "wide opening has been covered by a curtain while a stout wooden " +
        "door in the north wall leads back out into the " +
        "village of Hargnak.\n", LIGHT_ALL);
    add_item_light(({"shelf", "shelves", "wooden shelf", "wooden shelves"}),
        "The walls inside of this store are lined with plenty of solid, " +
        "wooden shelves, which are filled with all sorts of useful " +
        "goods. If you would like to purchase anything from the shelves, " +
        "there is a wooden sign sitting on the counter which gives you " +
        "the proper instructions.\n", LIGHT_ALL);
    add_item_light(({"goods", "useful goods"}),
        "There are plenty of interesting items here for sale, many of them " +
        "quite useful for anyone who travels around the world. You can read " +
        "the wooden sign on the counter to get a better idea of how you can " +
        "sort through these goods.\n", LIGHT_ALL);
    add_item_light(({"counter", "east wall", "wooden counter", 
        "ornate counter"}),
        "A rather ornate wooden counter runs along the entire length of the " +
        "eastern wall, a testament to the wealth and success of this local " +
        "merchant. A wooden sign stands upright on the counter, providing " +
        "instructions on how to do business in this store.\n", LIGHT_ALL);
    add_item_light(({"wooden sign", "sign"}),
        "This wooden sign has words etched into it and is perfect for " +
        "reading!\n", LIGHT_ALL);
    add_item_light(({"opening", "wide opening", "west wall", "curtain"}),
        "This wide opening has been covered with a green curtain, but a " +
        "quick peek tells you that there is nothing but storage for the " +
        "store's goods on the other side. Since you are obviously not " +
        "allowed to go there, you let the curtain drop and turn back into " +
        "the middle of the store.\n", LIGHT_ALL);
    add_item_light(({"door", "wooden door", "north wall"}),
        "This stout wooden door is finely constructed, just like everything " +
        "else in here. It sits in the middle of the north wall and leads " +
        "back out into the village of Hargnak.\n", LIGHT_ALL);
    add_item_light(({"windows", "window"}),
        "Windows? Who said anything about windows??? There are no windows " +
        "here, just a couple of fine oil lamps which keep the store brightly " +
        "lit.\n", LIGHT_ALL);
    add_item_light(({"wall", "walls"}),
        "Which wall did you wish to examine?\n", LIGHT_ALL);
    add_item_light(({"floor", "planks", "wooden planks"}),
        "Dozens of wide, wooden planks stretch across the floor of this " +
        "store, providing a clean, flat surface to walk upon.\n", LIGHT_ALL);
    add_item_light(({"south wall", "bin", "bins"}),
        "The south wall of the store has several bins of goods lined up " +
        "against it, hanging underneath the large banner.\n", LIGHT_ALL);
    add_item_light(({"ceiling", "beam", "beams", "wooden beams", 
        "wooden beam"}),
        "The ceiling of this store is of fairly simple construction, with " +
        "several wooden beams spanning the distance between the " +
        "walls.\n", LIGHT_ALL);
    add_item_light(({"banner", "large banner", "red banner"}),
        "  " +
        " \n", LIGHT_ALL);
    add_item_light(({"box", "boxes", "barrel", "barrels", "crate", "crates"}),
        "In almost every available square foot of this store, a variety of " +
        "boxes, barrels and crates have been neatly stacked and filled " +
        "with available goods. If you would like to purchase something " +
        "from them, please read the sign on the counter for " +
        "instructions.\n", LIGHT_ALL);

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT, LIGHT_BRIGHT);

    reset_room();

    config_default_trade();
    set_money_give_max(1000);
    set_store_room(GOBLINS_DIR + "harg_shop2");
    
    add_exit(GOBLINS_DIR + "hargnak2", "north", "@@village@@");
    add_exit(GOBLINS_DIR + "harg_shop2", "west", "@@shop@@");
}

int
village()
{
    write("\n\nYou open the door and walk back out into the village " +
        "of Hargnak.\n\n");
    return 0;
}

int
shop()
{
    write("You briefly consider trying to sneak past the curtain and into " +
        "the storage room of this store, but then you think better of it " +
        "and stay where you are.\n");
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
        notify_fail("Read what? The sign?\n");
        return 0;
    }
    if((str != "sign")  && (str != "wooden sign"))
    { 
        notify_fail("Read what? The sign?\n");
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

    if(!shopkeeper) shopkeeper = clone_object(GOBLINS_DIR + "npc/urguk.c");
    if (!present(shopkeeper)) shopkeeper->move_living("somewhere", this_object());
}

void
remove_object()
{
    shopkeeper->remove_object();
    ::remove_object();
}
