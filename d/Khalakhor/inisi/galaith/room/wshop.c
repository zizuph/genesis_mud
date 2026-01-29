/*********************************************************************
 * - shop1.c                                                       - *
 * - Created by Damaris 3/2003                                     - *
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
#define STORE  "/d/Khalakhor/inisi/galaith/room/wstore"
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
     return ({5, 9});
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
      "          |            Galaith Weaponry             |\n"+
      "          |     Jackwell Sillaith Proprietor        |\n"+
      "          |_________________________________________|\n"+
      "          |                                         |\n"+
      "          | Jackwell proudly supplies Galaith with  |\n"+
      "          | needed weapons and has also been known  |\n"+
      "          | to purchase weapons if they meet his    |\n"+
      "          | standards                               |\n"+
      "          |                                         |\n"+
      "          |                                         |\n"+
      "          | This shop operates like any shop. To    |\n"+
      "          | see what items are for sale please      |\n"+
      "          | use <list>.                             |\n"+
      "          |                                         |\n"+
      "          | You may also:                           |\n"+
      "          | cost <weapon/armour> for an estimate    |\n"+
      "          | sharpen <weapon> to sharpen the dull    |\n"+
      "          | wax <weapon>     to fix the rust        |\n"+
      "          | mend <armour>    to fix the dents       |\n"+
      "          |                                         |\n"+
      "          | We do not buy armours or other such non |\n"+
      "          | weapons.                                |\n"+
      "          |                                         |\n"+
      "          |      Thank you for your patronage.      |\n"+
      "          |                                         |\n"+
      "          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n"); 
}
public void
create_khalakhor_room()
{   
    object ob;
    set_short("Galaith Weaponry");
    set_long("   This is a small weaponry that has incredbly been placed "+
      "within this massive tree. It amazingly has been decorated with "+
      "many different weapons in all different shapes "+
      "and sizes. There is also a small sign next to a "+
      "large counter.\n");
    add_item(({"sign"}), query_shop_sign);
    add_item(({"shop", "room", "guest shop"}), query_long);
    add_item(({"wall", "walls"}),
      "The walls are light coloured with weapons scattered on "+
      "wooden displays.\n");
    add_item(({"counter", "small counter"}),
      "It is a small counter that has scratchesall over it's surface and "+
      "a small sign placed on it.\n");
    add_item(({"rack", "racks"}),
      "There are racks lined along two walls filled with many different "+
      "styles of weapons.\n");
    add_item(({"first rack"}),
      "The first rack is filled with daggers and small whips.\n");
    add_item(({"second rack"}),
      "The second rack has been filled with swords and polearms.\n");
       add_item(({"bell", "small bell", "brass bell"}),
      "It is a small brass bell.\n");
    add_item(({"bin", "storage bin"}),
      "This is a special storage bin that looks as if it has been "+
      "filled with a special oil to soak weapons in.\n");
/*********************************************************************
 * - The shop-related initializations.                             - *
 *********************************************************************/
    config_default_trade();
    set_money_give_max(1000);
    set_store_room(STORE);
    ob = clone_object(NPC+"jackwell");
    set_shopkeep(ob, this_object());
    set_smith(ob);

    add_exit("tree", "southeast");
    add_exit("wstore", "north", check_wizard);
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
        notify_fail("The shopkeeper isn't here.\n");
        return 0;
    }
    if (weapon_filter(ob)) return 1;
        notify_fail("");
        shopkeeper->command("say I purchase weapons only.");
        shopkeeper->command("say Go find someone else to take that "+
        "off your hands.");
        return 0;
}
int
do_bell(string str)
{
    if((str == "bell") || (str == "small bell") || (str == "brass bell"))
    {
	write("You pick up the small brass bell and ring it softly.\n");
	say(QCTNAME(TP)+" picks up the small brass bell and "+
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
    init_smith();
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
	write("The pugnant smell of oils and steel is everywhere.\n");
	return;
    }   
}
