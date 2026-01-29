/**********************************************************************
 * - dshop.c                                                        - *
 * - Dress shop in Samorgan                                         - *
 * - Created by Damaris@Genesis 08/2005                             - *
 **********************************************************************/
#pragma no_clone
#pragma no_inherit
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/basic.h"
inherit "/d/Khalakhor/std/room";
inherit "/d/Khalakhor/lib/shop";

#define STORE  "/d/Khalakhor/sw_speir/samorgan/room/mstore"
#define SHOPKEEP "/d/Khalakhor/sw_speir/samorgan/npc/brenetta"
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
	"          | `               SaMorgan Clothier             ` |\n"+
	"          | `         Brenetta Chalahan Proprietor        ` |\n"+
	"          | `       *`----------------------------`*      ` |\n"+
	"          | `                                             ` |\n"+
	"          | `                                             ` |\n"+
	"          | `     This shop proudly supplies the much     ` |\n"+
	"          | `     needed stylish and practical clothing   ` |\n"+
	"          | `     for men in SaMorgan.                    ` |\n"+
	"          | `                                             ` |\n"+
	"          | `     This shop operates like any shop.       ` |\n"+
	"          | `     To see what items are for sale          ` |\n"+
	"          | `     please use <list>.                      ` |\n"+
	"          | `                                             ` |\n"+
	"          | `     We do not buy items only sell.          ` |\n"+
	"          | `     Thank you for your patronage.           ` |\n"+
	"          | `                                             ` |\n"+
	"          | `                                             ` |\n"+
	"          | ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` |\n"+
	"          *--------------------*` - - `*--------------------*\n");
}

public void
create_khalakhor_room()
{
	set_short("A quiet clothing shop");
	set_long("\n   This is a quiet shop that has been artfully "+
	"decorated with long strands ribbons and fabrics in a very "+
	"dignified manner. There are clothing racks of many different "+
	"types of pants and doublets that line two walls. There is "+
	"also a small sign next to a small counter.\n");
	
	add_item(({"sign"}), query_shop_sign);
	add_item(({"shop", "room", "area"}), query_long);
	add_item(({"wall", "walls"}),
	"The walls are light coloured with lanterns and ribbons "+
	"placed in various spots.\n");
	add_item(({"counter", "small counter"}),
	"It is a small counter light in colour with bows, ribbons and "+
	"a small sign placed on it.\n");
	add_item(({"ribbon", "ribbons"}),
	"There are ribbons of many different colours that have been "+
	"draped and tied into bows along the counter and walls in "+
	"here.\n");
	add_item(({"bow", "bows"}),
	"Some ribbons have been tired into attractively festive bows.\n");
	add_item(({"fabric", "fabrics", "cloth", "cloths"}),
	"There are richly coloured fabrics in many different styles "+
	"draped elegantly around the room.\n");
	add_item(({"rack", "racks"}),
	"There are racks lined along two walls filled with many "+
	"different styles of clothing on them.\n");
	add_item(({"clothes", "clothing", "mens clothing"}),
	"There are too many clothes to look just look at, it might be "+
	"easier to 'list' them.\n");
	add_item(({"blue bow", "blue bows"}),
	"There are a few festive blue ribbons that have been elaborately "+
	"tied together to form a bow.\n");
	add_item(({"red bow", "red bows"}),
	"There are a few festive red ribbons that have been elaborately "+
	"tied together to form a bow.\n");
	add_item(({"yellow bow", "yellow bows"}),
	"There are a few festive yellow ribbons that have been "+
	"elaborately tied together to form a bow.\n");
	add_item(({"white bow", "white bows"}),
	"There are a few festive white ribbons that have been "+
	"elaborately tied together to form a bow.\n");
	add_item(({"green bow", "green bows"}),
	"There are a few festive green ribbons that have been "+
	"elaborately tied together to form a bow.\n");
	add_item(({"peach bow", "peach bows"}),
	"There are a few festive peach ribbons that have been "+
	"elaborately tied together to form a bow.\n");
	add_item(({"bell", "small bell", "gold bell"}),
	"It is a small gold bell.\n");
	add_item(({"north", "east", "south", "southeast", "southwest", "northeast", "northwest"}),
	"There is a wall in that direction.\n");
	add_item(({"west"}),
	"The street is in that direction.\n");    
    
/*********************************************************************
 * - The shop-related initializations.                             - *
 *********************************************************************/
        config_default_trade();
        set_money_give_max(1000);
        set_store_room(STORE);
        set_shopkeep(SHOPKEEP, this_object());
        
        add_exit("vil0506", "south");
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
