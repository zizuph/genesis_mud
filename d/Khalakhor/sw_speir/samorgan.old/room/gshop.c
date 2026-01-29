/**********************************************************************
 * - gshop.c                                                        - *
 * - General purpose shop.                                          - *
 * - Created by Damaris@Genesis 04/2006                             - *
 **********************************************************************/
#pragma no_clone
#pragma no_inherit
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/basic.h"
inherit "/d/Khalakhor/std/room";
inherit "/d/Khalakhor/lib/shop";

#define STORE  "/d/Khalakhor/sw_speir/samorgan/room/gstore"
#define SHOPKEEP "/d/Khalakhor/sw_speir/samorgan/npc/drew"
/*********************************************************************
 * - This adds the gks to the room so NPC's know where they are.   - *
 *********************************************************************/
public int *
query_local_coords()
{
	return ({4, 5});
}

public int *
query_global_coords()
{
	return ({0, 0});
}

string
query_shop_sign()
{
	return("\n"+
	"          *--------------------*` - - `*--------------------*\n"+
	"          | ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` |\n"+
	"          | `                                             ` |\n"+
	"          | `            SaMorgan General Shop            ` |\n"+
	"          | `          Drew Flannagan Proprietor          ` |\n"+
	"          | `       *`----------------------------`*      ` |\n"+
	"          | `                                             ` |\n"+
	"          | `                                             ` |\n"+
	"          | `    This general shop proudly serves the     ` |\n"+
	"          | `    villagers of SaMorgan with their needs.  ` |\n"+
	"          | `                                             ` |\n"+
	"          | `    This shop operates like any shop.        ` |\n"+
	"          | `    To see what items are for sale           ` |\n"+
	"          | `    please use <list>.                       ` |\n"+
	"          | `                                             ` |\n"+
	"          | `                                             ` |\n"+
	"          | ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` |\n"+
	"          *--------------------*` - - `*--------------------*\n");
}

public void
create_khalakhor_room()
{
	set_short("A small dimly lit shop");
	set_long("\n   A small dimly lit shop with a small counter in "+
	"one corner and a set of wooden shelves in the other. Upon the "+
	"far wall between the two is a small sign. The wooden floor is "+
	"scuffed up with quite a build up of dirt and grime.\n");
	
	add_item(({"sign"}), query_shop_sign);
	add_item(({"shop", "room", "area"}), query_long);
	add_item(({"wall", "walls"}),
	"The walls are dusty and slightly grimy.\n");
	add_item(({"counter", "small counter"}),
	"It is a small counter light in colour that has darkened with "+
	"wear.\n");
	add_item(({"shelves", "shelf"}),
	"To see what is there try to <list> them.\n");
	add_item(({"floor", "flooring"}),
	"the floor is made of wood and a bit dingy and dirty.\n");
	add_item(({"wood", "wooden"}),
	"The floor, counter and shelves are made from wood.\n");
	
	add_item(({"bell", "small bell", "gold bell"}),
	"It is a small gold bell.\n");
	add_item(({"north", "west", "east", "southeast", "southwest", "northeast", "northwest"}),
	"There is a wall in that direction.\n");
	add_item(({"south"}),
	"The street is in that direction.\n");
    
    
/*********************************************************************
 * - The shop-related initializations.                             - *
 *********************************************************************/
        config_default_trade();
        set_money_give_max(1000);
        set_store_room(STORE);
        set_shopkeep(SHOPKEEP, this_object());
        
        add_exit("vil0505", "south");
}    

int
do_sell(string str)
{
	write("Please read the sign.\n");
	return 1;
}

int
do_bell(string str)
{
	if((str == "bell") || (str == "small bell") || (str == "brass bell"))
	{
		write("You pick up the small gold bell and ring it "+
		"softly.\n");
		say(QCTNAME(TP)+" picks up the small gold bell and "+
		"rings it.\n");
		
		if (query_shopkeep())
		shopkeeper->command("say May I help you?");
		return 1;
	}
	return NF("Ring bell maybe?\n");
}

void
init()
{
	::init();
	init_shop();
	add_action(do_sell, "sell");
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
		write("The sweetest smell of jasmine soothes your "+
		"senses.\n");
		return;
	}   
}
