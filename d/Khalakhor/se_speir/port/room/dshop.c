/**********************************************************************
 * - dshop.c                                                        - *
 * - Dress shop in Macdunn                                          - *
 * - Created by Damaris@Genesis 01/2006                             - *
 **********************************************************************/
#pragma no_clone
#pragma no_inherit
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/basic.h"
inherit "/d/Khalakhor/std/room";
inherit "/d/Khalakhor/lib/shop";

#define STORE  "/d/Khalakhor/se_speir/port/room/dstore"
#define SHOPKEEP "/d/Khalakhor/se_speir/port/npc/peggy"
/*********************************************************************
 * - This adds the gks to the room so NPC's know where they are.   - *
 *********************************************************************/
int *
query_local_coords ()
{
  return ({4, 5});
}
int *
query_global_coords ()
{
  return ({0, 0});
}
string
query_shop_sign ()
{
  return("          +----------------------------------------+\n"+
         "          |           Macdunn Dress Shop           |\n"+
         "          |          Peggy Mae Proprietor          |\n"+
         "          |________________________________________|\n"+
         "          |                                        |\n"+
         "          |  This dress shop proudly supplies the  |\n"+
         "          |    much needed stylish and practical   |\n"+
         "          |     clothing for women in Macdunn.     |\n"+
         "          |                                        |\n"+
         "          |    This shop operates like any shop.   |\n"+
         "          |     To see what items are for sale     |\n"+
         "          |           please use <list>.           |\n"+
         "          |                                        |\n"+
         "          |    We do not buy items only sell.      |\n"+
         "          |     Thank you for your patronage.      |\n"+
         "          |                                        |\n"+
         "          +----------------------------------------+\n"); 
}


void
reset_room ()
{
  ::reset_room();
  if (!shopkeeper) {
    shopkeeper = clone_object(SHOPKEEP);
    shopkeeper->move(TO);
    tell_room(TO, QCTNAME(shopkeeper) + " wanders in from " +
              "the back room.\n");
    shopkeeper->set_shop(TO);
    shopkeeper->set_store_room(query_store_room());
    return;
  }
}
void
create_khalakhor_room ()
{
	set_short("A quaint dress shop");
	set_long("\n   This is a small but quaint dress shop. It is "+
           "tastefully decorated with ribbons and fabrics in a very "+
           "quaint nonobtrussive manner. There are racks of many "+
           "different types of dresses and gowns that line two walls. "+
           "There is also a small sign next to a small counter.\n");
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
	add_item(({"first rack"}),
           "The first rack is filled with fine dresses.\n");
	add_item(({"second rack"}),
           "The second rack is filled with gowns.\n");
	add_item(({"clothes", "clothing", "womens clothing"}),
           "There are too many clothes to look just look at, it might be "+
           "easier to 'list' them.\n");
	add_item(({"blue bow", "blue bows"}),
           "There are a few festive blue ribbons that are elaborately "+
           "tied together to form a bow.\n");
	add_item(({"red bow", "red bows"}),
           "There are a few festive red ribbons that are elaborately "+
           "tied together to form a bow.\n");
	add_item(({"yellow bow", "yellow bows"}),
           "There are a few festive yellow ribbons that are elaborately "+
           "tied together to form a bow.\n");
	add_item(({"white bow", "white bows"}),
           "There are a few festive white ribbons that are elaborately "+
           "tied together to form a bow.\n");
	add_item(({"green bow", "green bows"}),
           "There are a few festive green ribbons that are elaborately "+
           "tied together to form a bow.\n");
	add_item(({"peach bow", "peach bows"}),
           "There are a few festive peach ribbons that are elaborately "+
           "tied together to form a bow.\n");
	add_item(({"bell", "small bell", "gold bell"}),
           "It is a small gold bell.\n");
	add_item(({"north", "east", "south", "southeast", "southwest", "northeast", "northwest"}),
           "There is a wall in that direction.\n");
	add_item(({"west"}),
           "The doorway that leads to the road is in that direction.\n");
    
    
  /*********************************************************************
   * - The shop-related initializations.                             - *
   *********************************************************************/
  config_default_trade();
  set_money_give_max(1000);
  set_store_room(STORE);
  set_shopkeep(SHOPKEEP, this_object());
        
  add_exit("road_15_4", "west");
}    

int
do_sell (string str)
{
	write("Please read the sign.\n");
	return 1;
}

int
do_bell (string str)
{
	if(str == "bell" || str == "small bell" || str == "brass bell")	{
		write("You pick up the small gold bell and ring it "+
          "softly.\n");
		say(QCTNAME(TP)+" picks up the small gold bell and "+
        "rings it.\n");
		
		if (query_shopkeep())
      shopkeeper->command("say May I help you?");
		return 1;
	}
	return notify_fail("Ring bell maybe?\n");
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
	if (!strlen(str) || parse_command(str, ({}), "[the] 'air'")) {
		write("The sweetest smell of honeysuckle fills the air.\n");
		return;
	}   
}
