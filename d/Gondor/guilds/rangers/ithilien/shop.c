/*
 *  /d/Gondor/guilds/rangers/ithilien/shop.c
 *
 *
 * The shop of the Rangers of Ithilien.
 * - From the Hobbiton Shop, 1991, by Elessar.
 *
 * Modifications:
 * - Modified by Randor 1992
 * - Modified to use Olorin's standard-Gondor-shop, July 1994.
 * - 12-Oct-1998, Gnadnar: tidy up, add items
 * - 15-July-01, Alto: modified to fit revised rangers theme.
 * - 12-Aug-02, Gwyneth: Made it inherit a base ranger shop. No
 *      use holding the same code in three different shops.
 */
inherit "/d/Gondor/guilds/rangers/shop_base.c";

#include "../rangers.h"
#include "../shop_items.h"
#include "exit.c"

public void
create_ranger_shop()
{
    set_store_room(RANGERS_ITH_DIR + "store_room");
    set_short("the Henneth Annun Equipment Store");
    set_long("Provisional shelves line the walls of this low-roofed "
        + "chamber, and assorted equipment and tools are spread about "
        + "the floor. An open doorway in the south wall leads back to "
        + "the main cave, and a poster hangs to the left of the doorway.\n");
    set_shop_name("The Rangers of Ithilien Equipment Shop");
    set_keeper_file(RANGERS_NPC + "isildil");
    add_item( ({ "cave", "low-roofed chamber", "chamber" }), "The chamber "
        + "is not large, and the stacks of equipment make it seem even "
        + "smaller.\n");
    add_item( ({ "shelf", "provisional shelves", "shelves" }), "The shelves "
        + "-- a makeshift arrangement -- are just rough planks attached to "
        + "the walls. They seem secure enough to hold small items, but the "
        + "heavier equipment lies on the floor.\n");
    add_item( ({ "wood", "plank", "planks" }), "The planks are bare, "
        + "unvarnished wood.\n");
    add_item("floor", "Equipment and tools are spread on the floor along "
        + "the walls of the chamber, but the center of the floor is clear "
        + "and seems to have been recently swept.\n");
    add_item( ({ "wall", "walls" }), "Except for the shelves holding "
        + "equipment and a poster near the doorway, the rock walls are "
        + "bare.\n");
    add_item( ({ "roof", "ceiling" }), "Dark grey rock is close overhead.\n");
    add_item( ({ "stone", "rock" }), "Floor, walls and ceiling all are "
        + "dark grey rock.\n");
    add_item( ({ "pile", "piles", "stack", "stacks", "tool", "tools",
        "equipment", }), "The shelves hold jars, flasks, lamps and other "
        + "small or fragile items, while pouches, backpacks, cloaks and "
        + "lother arge or unbreakable equipment is spread around the "
        + "floor.\n");
    add_item( ({ "door", "open doorway", "doorway" }), "An open doorway "
        + "leads south to a larger chamber.\n");
    add_item( ({ "main cave", "larger chamber" }), "The cave to the south "
        + "is considerably larger; it appears to the main chamber in this "
        + "underground complex.\n");

    add_prop(ROOM_M_NO_SCRY, 1);
    add_exit(RANGERS_ITH_DIR + "rockchamber", "south",
        &check_ranger(0, keeper));

    set_standard_equip(ITH_EQUIP);
}

public string
exa_poster()
{
  return "\nThis is the Equipment Store of Henneth Annun.\n" +
         "You can try these instructions: \n" +
         "    buy sword for gold and get copper back\n" +
         "    buy sword for gold coins\n" +
         "    sell sword for copper coins\n" +
         "    sell all  - will let you sell all items except for\n" +
         "                items you wield or wear.\n" +
         "    sell all! - will let you sell ALL items you have, well\n" +
         "                at least the droppable, and no coins.\n" +
         "    sell sword, sell second sword, sell sword 2, sell two swords\n" +
         "                also works. You might want to change the verb to\n" +
         "                'value' or 'buy' too. Beware, you will never buy\n"+
         "                more than one item at a time. So if you really\n" +
         "                want those three expensive swords, you have to \n" +
         "                repeat yourself three times.\n" +
         "    If you want a list of the special equipment available, do:\n"+
         "     'list equipment'.\n"+
         "    If you want a list of all swords available in the store, the\n" +
         "    correct syntax is: list swords\n" +
         "                'list weapons', 'list armours' also works.\n\n";
}
