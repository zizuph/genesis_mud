/*
 * Dol Guldur Shop - /d/Gondor/rhovanion/dolguldur/main2.c
 *
 * Varian - November 2020
 */

#pragma strict_types

#include "/d/Gondor/rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Gondor/std/room";
inherit "/lib/shop.c";
inherit "/d/Emerald/lib/shop_list";

static object merch;

void
create_gondor()
{
    set_short("Rushk's Goods");
    set_long("You are standing inside a small shack quaintly named " +
        "'Rushk's Goods'. At least, that's what it says on the poster " +
        "beside the wooden counter that runs along the eastern wall. " +
        "Behind the counter you notice a narrow opening that reveals " +
        "the shop's storage room, while the doorway in the western " +
        "wall leads back out into the city of Dol Guldur.\n");

    add_item( ({"counter", "wood counter", "wooden counter"}),
        "This wooden counter is pretty beat up, having been " +
        "thrown together with bits of salvaged wood. It seems to " +
        "be strong enough to serve its purpose however.\n");
    add_item( ({"wall", "walls"}),
        "The walls of this shack have been pieced together from thousands " +
        "of broken planks, all cobbled together to complete the wall.\n");
    add_item( ({"up", "ceiling"}),
        "The ceiling of this small shack has been constructed from " +
        "overlapping wooden slats on top of a jumble of wooden beams.\n");
    add_item( ({"down", "floor"}),
        "The floor of this shack is nothing more than hard-packed dirt.\n");
    add_item( ({"opening", "storage room", "store room"}),
        "You are able to see the storage from for this shop through " +
        "the opening behind the counter in the east wall.\n");
    add_item( ({"door", "doorway"}),
        "This doorway leads back out to the city of Dol Guldur.\n");
    add_item( ({"plank", "wooden plank", "planks", "wooden planks",
            "broken plank", "broken planks"}),
        "These wooden planks have clearly been salvaged from the wreckage " +
        "amongst the ruins of Dol Guldur. The planks are all weathered " +
        "and cracked, not to mention of various lengths, widths and even " +
        "different thicknesses. However, someone has managed to make it " +
        "work, as the walls keep out the wind and cold.\n");
    add_item( ({"slat", "slats", "wooden slat", "wooden slats"}),
        "These wooden slats are overlapping as they sit on the wooden " +
        "beams. There doesn't seem to be too many leaks at least.\n");
    add_item( ({"beam", "beams", "wooden beam", "wooden beams"}),
        "There are dozens of wooden beams of various sizes running in " +
        "every direction across the ceiling as they support the wooden " +
        "slats that make up the roof.\n");
    add_item( ({"wood", "wooden"}),
        "There are plenty of things here made of wood, could you be " +
        "more specific?\n");
    add_item( ({"dirt", " hard-packed dirt", "packed dirt"}),
        "It's dirt. And it's hard packed too.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(DG_DIR + "main1", "west", 0, 0, 0);
    add_exit(DG_DIR + "shop2", "east", "@@shop@@", 0, 1);

    set_no_exit_msg( ({"north", "northeast", "southeast", "south",
            "southwest", "northwest"}),
        "The walls of the shack prevent you from going in that direction.\n");

    reset_room();

    config_default_trade();
    set_money_give_max(1000);
    set_store_room(DG_DIR + "shop2");

}

int
shop()
{
    write("You were going to enter the storage room, but then think " +
        "better of it.\n");
    return 1;
}

void
init()
{
    ::init();
    init_shop();
    add_action("do_read", "read");
}

int
do_read(string str)
{
    if(!str)
    {
        notify_fail("Read what? The poster?\n");
        return 0;
    }
    if( (str != "sign") && (str != "poster") )
    { 
        notify_fail("Read what? The poster?\n");
        return 0;
    }

    write("RUSHK'S GOODS!\n" +
        "You can try these instructions: \n" +
        "buy sword for gold coins    (default: the smallest denomination)\n" +
        "buy sword for gold and get copper back\n" +
        "sell sword for copper coins (default: the largest denomination)\n" +
        "sell all  - will let you sell all items except for items you " +
        "wield\n" +
        "            or wear. Beware that if you have many items to sell,\n" +
        "            check whether you have sold all or repeat the " +
        "command.\n" +
        "sell all! - will let you sell ALL items you have, well at least " +
        "the\n" +
        "            droppable ones, and no coins. (see warning at 'sell " +
        "all')\n" +
        "sell sword, sell second sword, sell sword 2, sell two swords " +
        "also\n" +
        "            works. Beware, you will never buy more than one item " +
        "at\n" +
        "            a time. So if you really those three expensive " +
        "swords, you\n" +
        "            have to repeat yourself three times.\n" +
        "value     - will value an item you carry before you decide to " +
        "sell it.\n" +
        "show      - appraise one of the items in stock before you buy " +
        "it.\n" +
        "list      - will list the items in stock, 'list armour' and " +
        "'list\n" +
        "            weapon' are valid commands, or e.g. 'list sword'.\n" +
        "            multiple types can be listed as well, e.g. 'list " +
        "axe,\n" +
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

    if(!merch) merch = clone_object(DG_DIR + "npc/rushk.c");
    if (!present(merch)) merch->move_living("somewhere", this_object());
}

void
remove_object()
{
    merch->remove_object();
    ::remove_object();
}
