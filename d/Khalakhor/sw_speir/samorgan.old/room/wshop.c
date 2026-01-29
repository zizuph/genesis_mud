/*********************************************************************
 * - wshop.c                                                       - *
 * - Created by Damaris 7/2005                                     - *
 * Typo fixed by Gronkas Jan. 4, 2017: isn't --> is not because
 * some apostroph were no ASCII chars
 *********************************************************************/
#pragma no_clone
#pragma no_inherit
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"
inherit "/d/Khalakhor/std/room";
inherit "/d/Khalakhor/lib/shop";
inherit "/d/Khalakhor/lib/smith";
#define STORE  "/d/Khalakhor/sw_speir/samorgan/room/wstore"
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
	"          |            SaMorgan Weaponry            |\n"+
	"          |         Emmit Konner Proprietor         |\n"+
	"          |_________________________________________|\n"+
	"          |                                         |\n"+
	"          | Emmit proudly supplies SaMorgan with    |\n"+
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
	set_short("SaMorgan Weaponry");
	set_long("   This small but quaint weaponry shop is a "+
	"necessity for the small village of SaMorgan. The walls "+
	"are lined up with different sheets of metal, moldings "+
	"and fittings. Through the breezeway a large forge can "+
	"be seen from here but it is quite obvious that only the "+
	"proprietor is allowed access. There is not much else to "+
	"see other than a couple of workbenches and a sign posted "+
	"next to a large counter.\n");
	
	add_item(({"sign"}), query_shop_sign);
	add_item(({"shop", "room", "guest shop"}), query_long);
	add_item(({"wall", "walls"}),
	"The walls are light coloured with weapons scattered on "+
	"wooden displays.\n");
	add_item(({"counter", "large counter"}),
	"It is a large counter that has scratches all over it's "+
	"surface and a sign placed next to it.\n");
	add_item(({"rack", "racks"}),
	"There are racks lined along two walls filled with many "+
	"different styles of weapons.\n");
	add_item(({"first rack"}),
	"The first rack is filled with daggers and small whips.\n");
	add_item(({"second rack"}),
	"The second rack has been filled with swords and polearms.\n");
	add_item(({"bell", "small bell", "brass bell"}),
	"It is a small brass bell.\n");
	add_item(({"bin", "storage bin"}),
	"This is a special storage bin that looks as if it has been "+
	"filled with a special oil to soak weapons in.\n");
	add_item(({"workbench", "workbenches"}),
	"There are a couple of workbenches here with newly fashioned "+
	"weapons on them.\n");
	add_item(({"new weapons"}),
	"Please <read sign>.\n");
	add_item(({"breezeway"}),
	"Through the breezeway there can be seen a large forege.\n");
	add_item(({"northeast", "north"}),
	"The village is back out in that direction.\n");
	add_item(({"southwest", "southeast", "northwest", "north", "east"}),
	"There is a wall in that direction.\n");
	add_item(({"south"}),
	"The storeroom is in that direction.\n");
	add_item(({"southwest"}),
	"There is a breezeway in that direction that leads to the "+
	"forge.\n");
	add_item(({"forge"}),
	"The forge can be seen through the breezeway.\n");    
    
/*********************************************************************
 * - The shop-related initializations.                             - *
 *********************************************************************/
        config_default_trade();
        set_money_give_max(1000);
        set_store_room(STORE);
        ob = clone_object(NPC+"emmit");
        set_shopkeep(ob, this_object());
        set_smith(ob);
        
        add_exit("vil0704", "north");
        // add_exit("wsmith", "west");
        add_exit("vil0705", "northeast");
        
        add_exit("wstore", "south", check_wizard);
        add_fail(({"east", "southeast", "northwest", "southwest"}),
        "You walked into a wall!\n"+
        "Ouch! That's gotta hurt!\n");
        add_fail("southwest", "Only the proprietor may enter the "+
        "forge.\n");
}

int
shop_hook_allow_buy(object ob)
{
	if (NOSHOPKEEP)
	{
		notify_fail("The shopkeeper is not here.\n");
		return 0;
	}
	return 1;
}

int
shop_hook_allow_sell(object ob)
{
	if (NOSHOPKEEP)
	{
		notify_fail("The shopkeeper is not here.\n");
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
		write("You pick up the small brass bell and ring it "+
		"softly.\n");
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
		write("The pugnant smell of oil mingled with metal "+
		"is everywhere.\n");
		return;
	}   
}
