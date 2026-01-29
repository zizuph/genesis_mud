/*********************************************************************
 * - gshop.c                                                       - *
 * - This is the guest shop of the Gentlemans Club located in      - *
 * - Drakmere                                                      - *
 * - Created by Damaris 10/2001                                    - *
 * - Last Modified by Damaris 1/2/2002                             - *
 *********************************************************************/
#pragma no_clone
#pragma no_inherit
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "/d/Raumdor/defs.h"
#include "../guild.h"
inherit CLUB;
inherit "/d/Raumdor/lib/shop";

#define STORE  "/d/Raumdor/guilds/gc/room/gstore"
string
query_shop_sign()
{
    return("          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n"+
      "          |         The Gentleman's Club           |\n"+
      "          |             Guest shop                 |\n"+
      "          |________________________________________|\n"+
      "          |                                        |\n"+
      "          |  The Gentleman's Club proudly supplies |\n"+
      "          |  it's members and guests with the much |\n"+
      "          |  needed stylish and practical clothing |\n"+
      "          |           for men and women            |\n"+
      "          |                                        |\n"+
      "          |    This shop operates like any shop.   |\n"+
      "          |     To see what items are for sale     |\n"+
      "          |           please use <list>.           |\n"+
      "          |                                        |\n"+
      "          |    We do not buy items only sell.      |\n"+
      "          |     Thank you for your patronage.      |\n"+
      "          |                                        |\n"+
      "          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n"); 
}
public void
create_guild_room()
{
    set_short("A Guest shop");
    set_long("This is a small shop that has been elaborately "+
      "decorated with ribbons and fabrics in a very tasteful "+
      "manner. There are racks of many different types of clothing "+
      "that line two walls. There is also a small sign next to a "+
      "large counter.\n");
    add_item(({"sign"}), query_shop_sign);
    add_item(({"shop", "room", "guest shop"}), query_long);
    add_item(({"wall", "walls"}),
      "The walls are light coloured with lanterns and ribbons "+
      "placed in various spots.\n");
    add_item(({"counter", "small counter"}),
      "It is a small counter light in colour with bows, ribbons and "+
      "a small sign placed on it.\n");
    add_item(({"ribbon", "ribbons"}),
      "There are ribbons of many different colours that have been "+
      "draped and tied into bows along the counter and walls in here.\n");
    add_item(({"bow", "bows"}),
      "Some ribbons have been tired into attractively festive bows.\n");
    add_item(({"fabric", "fabrics", "cloth", "cloths"}),
      "There are richly coloured fabrics in many different styles "+
      "draped elegantly around the room.\n");
    add_item(({"rack", "racks"}),
      "There are racks lined along two walls filled with many different "+
      "styles of clothing on them.\n");
    add_item(({"first rack"}),
      "The first rack is filled with clothing for gentleman.\n");
    add_item(({"second rack"}),
      "The second rack has been filled with clothing for women.\n");
    add_item(({"clothes", "clothing", "womens clothing", "gentlemans clothing"}),
      "There are too many clothes to look just look at, it might be "+
      "easier to 'list' them.\n");
    add_item(({"blue bow", "blue bows"}),
      "There are a few festive blue ribbons that have been elaborately "+
      "tied together to form a bow.\n");
    add_item(({"red bow", "red bows"}),
      "There are a few festive red ribbons that have been elaborately "+
      "tied together to form a bow.\n");
    add_item(({"yellow bow", "yellow bows"}),
      "There are a few festive yellow ribbons that have been elaborately "+
      "tied together to form a bow.\n");
    add_item(({"white bow", "white bows"}),
      "There are a few festive white ribbons that have been elaborately "+
      "tied together to form a bow.\n");
    add_item(({"green bow", "green bows"}),
      "There are a few festive green ribbons that have been elaborately "+
      "tied together to form a bow.\n");
    add_item(({"peach bow", "peach bows"}),
      "There are a few festive peach ribbons that have been elaborately "+
      "tied together to form a bow.\n");
    add_item(({"bell", "small bell", "gold bell"}),
      "It is a small gold bell.\n");
/*********************************************************************
 * - The shop-related initializations.                             - *
 *********************************************************************/
    config_default_trade();
    set_money_give_max(1000);
    set_store_room(STORE);
    set_shopkeep(GUILD_DIR + "npc/adreas", this_object());

    add_exit("join", "north");
    add_exit("gstore", "storeroom", 0, 0, 1);
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
	write("You pick up the small gold bell and ring it softly.\n");
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
	write("The sweetest smell of jasmine soothes your senses.\n");
	return;
    }   
}

