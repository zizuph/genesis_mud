/* Updated 9-23-2001 by Damaris, because she grew tired of runtime errors
 * Updated 10/2004 by Damaris, added trash barrel to assist with 
 * increased uptimes.
 */
#pragma strict_types
#include "../default.h"
#include <macros.h>
#include <stdproperties.h> 


inherit CVAN_ROOM;
inherit "/d/Kalad/lib/shop";

#define STORE	(CVAN + "shop/store")

string
query_shop_sign()
{
    return("          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n"+
      "          |         Kabal General Store            |\n"+
      "          |________________________________________|\n"+
      "          |                                        |\n"+
      "          |   This shop operates like any other.   |\n"+
      "          |   You may <buy> or <sell>.             |\n"+
      "          |   To see what items are for sale       |\n"+
      "          |          please use <list>.            |\n"+
      "          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n"); 
}

public void
create_cvan_room()
{
    set_short("The Kabal general store");
    set_long("This is the general store of the Caravan district, peering "+
      "ahead of you, you can see a large wooden counter behind which sits "+
      "the shopkeeper, Anthios. Behind him you can see racks filled with "+
      "all manner of goods, brought here by travelling merchants or the "+
      "occasional adventurer. A large sign hangs over the counter.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_item(({"sign"}), query_shop_sign);
    add_item(({"bell", "small bell", "brass bell"}),
      "A small bell made of brass, that is used to ring for service.\n");
      
    /*
     * The shop-related initializations.
     */
    config_default_trade();
    set_money_give_max(1000);
    set_store_room(STORE);
    set_shopkeep(NPC + "gsowner", this_object());
    clone_here(OBJ + "tbarrel")->move(this_object());
    add_exit(CVAN + "shop/store", "west", wiz_check, 0, 1);
    add_exit(CVAN + "caravan/s3", "east");

}
int
do_bell(string str)
{
    if((str == "bell") || (str == "small bell") || (str == "brass bell"))
    {
	write("You pick up the small brass bell and ring it loudly.\n");
	say(QCTNAME(TP)+" picks up the small brass bell and "+
	  "rings it loudly.\n");

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

    /*
     * Do this to add the shop-commands to the player.
     */
    init_shop();
    add_action(do_bell, "ring");
}


