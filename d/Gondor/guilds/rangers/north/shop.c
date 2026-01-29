/*
 *  /d/Gondor/guilds/rangers/north/shop.c
 *
 *  Jerret's Equipment Store  *  rewritten by Arren  september 1993
 *  - use /lib/shop  - copied from ranger guild shop
 *  modified by Arren, from Olorin's shop in Minas Morgul
 *  15-July-01, Alto: modified to fit revised rangers theme.
 *  12-Aug-02, Gwyneth: Made it inherit a base ranger shop. No
 *      use holding the same code in three different shops.
 *
 */
inherit "/d/Gondor/guilds/rangers/shop_base.c";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include "../rangers.h"
#include "../shop_items.h"
#include "check_exit.c"

public void
create_ranger_shop()
{
    set_store_room(RANGERS_NOR_DIR + "store_room");
    set_short("Jerret's Equipment Store");
    set_long("This is Jerret's Equipment Store. Inside this high round "
        + "room you can sell or buy all kind of things. The owner has "
        + "hung a poster on the wall, which you can read if you like. "
        + "The shopkeeper can value things if you want him to. Buying and "
        + "selling things is encouraged by the shopkeeper.\n");
    set_shop_name("The Rangers of the North Equipment Shop");
    set_keeper_file(RANGERS_NPC + "jerret");
    add_item(({"door"}), "The door is probably leading into the storeroom "
        + "of the shop. The door is standing open, but the shop keeper "
        + "probably would not be amused if you tried to go there.\n");

    add_exit(RANGERS_NOR_DIR + "w_corridor", "north");
    add_exit(RANGERS_NOR_DIR + "s_corridor", "east");

    set_standard_equip(NORTH_EQUIP);
    add_prop(ROOM_M_NO_SCRY, 1);
}

public string
exa_poster()
{
  return "\nThis is Jerret's Equipment Store.\n" +
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
