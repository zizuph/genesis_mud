/*********************************************************************
 * - shop.c                                                        - *
 * - Created by Damaris 4/2003                                     - *
 *********************************************************************/
#pragma no_clone
#pragma no_inherit
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/basic.h"
#include "../defs.h"
inherit "/d/Khalakhor/std/room";
inherit "/d/Khalakhor/lib/shop";
inherit "/d/Khalakhor/lib/smith";
#define STORE  "/d/Khalakhor/inisi/galaith/room/store"
#define NOSHOPKEEP !objectp(present(query_shopkeep(), TO))
/*
 * Prototype.
 */
int check_wizard();
 /*********************************************************************
  * - This adds the gks to the room so NPC's know where they are.   - *
  *********************************************************************/
 public int *
 query_local_coords()
 {
     return ({5, 13});
 }
 public int *
 query_global_coords()
 {
     return ({0, 0});
}
string
query_shop_sign()
{
    return("          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n"+
      "          |              General Store              |\n"+
      "          |        Milith Silith Proprietor         |\n"+
      "          |_________________________________________|\n"+
      "          |                                         |\n"+
      "          | Milith proudly supplies Galaith with    |\n"+
      "          | needed supplies and has also been known |\n"+
      "          | to purchase items as well if they meet  |\n"+
      "          | her standards.                          |\n"+
      "          |                                         |\n"+
      "          | This shop operates like any shop. To    |\n"+
      "          | see what items are for sale please      |\n"+
      "          | use <list>.                             |\n"+
      "          |                                         |\n"+
      "          |                                         |\n"+
      "          |      Thank you for your patronage.      |\n"+
      "          |                                         |\n"+
      "          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n"); 
}
public void
create_khalakhor_room()
{
    object ob;
    set_short("A general store");
    set_long("   This is a small general store that has "+
      "diligently been placed within this massive magical tree. "+
      "It amazingly has been decorated with many different shelves "+
      "in all different shapes and sizes that are interwoven with "+
      "the tree. There is also a small sign placed next to an "+
      "intimate counter that has a small glass bell resting upon it.\n");
    add_item(({"sign"}), query_shop_sign);
    add_item(({"shop", "tree", "room", "general store"}), query_long);
    add_item(({"walls", "wall"}),
      "The walls are simply made from bark and there is a "+
      "mysterious light emanating from it.\n");
    add_item(({"floor", "ground"}),
      "The floor on which you are standing seems very firm, and is " +
      "made from the tree. It appears the tree has grown limbs " +
      "intertwine just to create the floor.\n");
    add_item(({"bell", "small bell", "glass bell"}),
      "It is a small glass bell that has a rainbow etched in the glass "+
      "and it even shimmers with rainbow colours in the light.\n");
    add_item(({"counter", "intimate counter"}),
      "The counter has multiple knots in it and is growing out from "+
      "the walls of the tree. There is a small glass bell resting upon "+
      "it's surface and a sign next to it.\n");
    add_item(({"shelf", "shelves"}),
      "The shelves are many different sizes and have been interwoven "+
      "with the tree and filled with many different items.\n");
    add_item(({"light"}),
      "A strange light seems to eminate from the tree itself and casts "+
      "a warm glow in this area.\n");

/*********************************************************************
 * - The shop-related initializations.                             - *
 *********************************************************************/
    config_default_trade();
    set_money_give_max(1000);
    set_store_room(STORE);
    ob = clone_object(NPC+"milith");
    set_shopkeep(ob, this_object());
    set_smith(ob);
    add_exit("tree", "east");
    add_exit("store", "west", check_wizard);
    add_fail("auto", "You walked into a wall!\n"+
      "Ouch! That's gotta hurt!\n");

}    

int
shop_hook_allow_buy(object ob)
{
    if (NOSHOPKEEP)
    {
        notify_fail("the shopkeeper isn't here.\n");
        return 0;
    }
    return 1;
}
int
shop_hook_allow_sell(object ob)
{
    if (NOSHOPKEEP)
    {
        notify_fail("the shopkeeper isn't here.\n");
        return 0;
    }
    return 1;
}
int
do_bell(string str)
{
    if((str == "bell") || (str == "small bell") || (str == "glass bell"))
    {
	write("You pick up the small glass bell and ring it softly.\n");
	say(QCTNAME(TP)+" picks up the small glass bell and "+
	  "rings it.\n");


	if (query_shopkeep())
	    shopkeeper->command("say May I help you?");

	return 1;
    }
    return NF("Ring bell maybe?\n");
}
/*
 * We do not want mortal players to walk into the storeroom and help
 * themselves. However, wizards might need to go in there if something
 * is wrong. Therefore we block their exit.
 */
int
check_wizard()
{
    /* wizards may use the exit. */
    if (this_player()->query_wiz_level())
    {
        return 0;
    }

    /* however, mortal players cannot... */
    write("The storeroom is locked so you may not enter.\n");
    say(QCTNAME(this_player()) + " fails to enter the storeroom.\n");
    return 1;
}
void
init()
{
    ::init();
    init_shop();
    add_action(do_bell, "ring");
}

/*********************************************************************
 * - This is for smells in the room.                               - *
 *********************************************************************/
void
hook_smelled(string str)
{
    if (!strlen(str) || parse_command(str, ({}), "[the] 'air'"))
    {
	write("The fresh smell of pine is everywhere.\n");
	return;
    }   
}
