/*
 * /d/Gondor/common/guild/ithilien/shop.c
 *
 *
 * The shop of the Rangers of Ithilien.
 * - From the Hobbiton Shop, 1991, by Elessar.
 *
 * Modifications:
 * - Modified by Randor 1992
 * - Modified to use Olorin's standard-Gondor-shop, July 1994.
 * - 12-Oct-1998, Gnadnar: tidy up, add items
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild/gondor/shop.c";

#include "/d/Gondor/common/guild/lib/shop_items.h"
#include "/d/Gondor/defs.h"

#define STORE_ROOM (RANGER_ITH_DIR + "store")  /* Where the items are stored */

/* prototypes */
public void	create_shop();
public string	exa_poster();



/*
 * Function name:	create_shop
 * Description	:	set up the shop
 */
public void
create_shop()
{
    set_store_room(STORE_ROOM);
    set_short("the Henneth Annun Equipment Store");
    set_long(BSN(
	"Provisional shelves line the walls of this low-roofed chamber, "+
	"and assorted equipment and tools are spread about the floor. An "+
	"open doorway in the south wall leads back to the main cave, and "+
	"a poster hangs to the left of the doorway."));
    set_shop_name("The Henneth Annun Equipment Store");
    set_keeper_file(RANGER_ITH_DIR + "npc/isildil");
    set_no_sell_prop( ({ GONDOR_M_RANGERS_NO_SELL,
			 GONDOR_M_ROHIRRIM_NO_SELL,
			 GONDOR_M_TIRITH_NO_SELL }) );
    set_hated_race( ({"goblin"}) );
    set_favoured_race( ({ "human", "elf" }) );
    set_money_greed_buy(discriminate);
    set_money_greed_sell(discriminate);
    set_money_greed_change(discriminate);
    set_standard_equip(ITH_EQUIP);

    add_exit((RANGER_ITH_DIR + "rockchamber"), "south", 0, 0);

    add_item("notebook", "@@look_notebook");
    add_item( ({ "cave", "low-roofed chamber", "chamber" }), BSN(
	"The chamber is not large, and the stacks of equipment "+
	"make it seem even smaller."));
    add_item( ({ "shelf", "provisional shelves", "shelves" }), BSN(
	"The shelves -- a makeshift arrangement -- are just rough planks "+
	"attached to the walls. They seem secure enough to hold small "+
	"items, but the heavier equipment lies on the floor."));
    add_item( ({ "wood", "plank", "planks" }),
	"The planks are bare, unvarnished wood.\n");
    add_item("floor", BSN(
	"Equipment and tools are spread on the floor along the walls of "+
	"the chamber, but the center of the floor is clear and seems "+
	"to have been recently swept."));
    add_item( ({ "wall", "walls" }), BSN(
	"Except for the shelves holding equipment and a poster near the "+
	"doorway, the rock walls are bare."));
    add_item( ({ "roof", "ceiling" }),
	"Dark grey rock is close overhead.\n");
    add_item( ({ "stone", "rock" }),
	"Floor, walls and ceiling all are dark grey rock.\n");
    add_item( ({ "pile", "piles", "stack", "stacks", "tool", "tools",
	"equipment", }), BSN(
	"The shelves hold jars, flasks, lamps and other small or fragile "+
	"items, while pouches, backpacks, cloaks and other large or "+
	"unbreakable equipment is spread around the floor."));
    add_item( ({ "door", "open doorway", "doorway" }),
	"An open doorway leads south to a larger chamber.\n");
    add_item( ({ "main cave", "larger chamber" }), BSN(
	"The cave to the south is considerably larger; it appears to "+
	"the main chamber in this underground complex."));

} /* create_shop */



/*
 * Function name:	exa_poster
 * Description	:	handle read/exa poster
 * Returns	:	string -- the poster text
 */
public string
exa_poster()
{
  return "\nWelcome to the Henneth Annun Equipment Store!\n" +
         "You can try these actions: \n" +
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
         "    If you want a list of all swords available in the store, the\n" +
         "    correct syntax is: list swords\n" +
         "                'list weapons', 'list armours' also works.\n\n";
} /* exa_poster */
