/* spplmrch.c: The general supply store of Tyr.
 * Updated to Raumdor inherits and standards
 * Also placed a non-readable, but examinable sign here
 * Damaris 5/2001
 */
inherit "/std/room";
inherit "/d/Cirath/lib/shop";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "/d/Cirath/common/mobber.h"


#define SHOPKEEP "trink"
#define STORE "/d/Cirath/tyr/caravan/spplstor.c"
#define GONEFISHING !objectp(present(SHOPKEEP, TO))

string
query_shop_sign()
{
    return("\n        You examine the symbols and interpret the sign as.\n\n"+
      "          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n"+
      "          |            The Tarnished cup           |\n"+
      "          |________________________________________|\n"+
      "          |                                        |\n"+
      "          |     Trink proudly trades here in Tyr.  |\n"+
      "          |                                        |\n"+
      "          |   This shop operates like any other.   |\n"+
      "          |   To see what items are for sale       |\n"+
      "          |          please use <list>.            |\n"+
      "          |                                        |\n"+
      "          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n"); 
}

void
create_room()
{
    ::create_room();
    set_short("the tarnished cup");
    set_long("Within the large tent hang goods of all sorts, from the "+
             "mundane to the strange. The quality is less than ideal as the "+
             "name of the bazaar, The Tarnished Cup, implies, but at "+
             "least the merchandise is not broken. Caravan Way lies "+
             "south and a huge stone slab rests on what could be tunnel "+
             "downwards.\n");
    add_item(({"sign"}), query_shop_sign);
    add_item(({"slab", "stone slab"}), "Its a big rock, nothing more.\n");
    add_cmd_item(({"slab", "stone slab"}), ({"lift","move","pull","push"}),
             "Just how strong do you think you are anyway?\n");
    INSIDE
    /*
     * The shop-related initializations.
     */
    config_default_trade();
    set_money_give_max(1000);
    set_store_room(STORE);
    set_shopkeep(TYR_NPC+"sppldude.c", this_object());
    
    add_exit(TYR_CARAVAN+"rd_cw_02.c", "south", 0, 1);
    add_exit(STORE, "down", wiz_check, 0, 1);

    reset_room();
}

int
shop_hook_allow_sell(object ob)
{
    if (GONEFISHING)
    {
        notify_fail("Sell to who?\n");
        return 0;
    }
    if ((armour_filter(ob))||(weapon_filter(ob)))
    {
        notify_fail("The bazaar doesn't deal in armnament\n");
        return 0;
    }
    return 1;
}

int
shop_hook_allow_buy(object ob)
{
    if (GONEFISHING)
    {
        notify_fail("Nobody seems to be here to sell you anything.\n");
        return 0;
    }
    return 1;
}
int
do_read(string str)
{
    if (str != "sign")
    {
	notify_fail("Read what?\n");
	return 0;
    }

    write("It is forbidden to read in Tyr.\n");
    return 1;
}
      
void init()
{
    ::init();
    init_shop();
    add_action(do_read, "read");
}
