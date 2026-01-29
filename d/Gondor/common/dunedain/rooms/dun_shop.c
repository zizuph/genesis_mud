/*
 *  The shop in the Dunedain guild
 *
 *  Olorin, 18-nov-1994
 *
 *	Copyright (c) 1994, 1995, 1996 by Christian Markus
 *
 * Updated shop listing
 * Finwe December 2017
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/lib/shop.c";
inherit "/d/Faerun/lib/shop_list";

#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/dunedain/lib/dunedain_defs.h"

#define STORE_ROOM	(DUNEDAIN_DIR + "rooms/dun_store")
#define MT_WEAPON	(MINAS_DIR + "obj/mt_weapon")

public void
create_shop()
{
    set_store_room(STORE_ROOM);

    set_short("the Armoury of the House of the Dunedain");
    set_shop_name("the Armoury of the House of the Dunedain");
    set_long(BSN(
        "This is the Armoury of the House of the Dunedain. Here the "
        + "members of the Houses can buy and sell weapons and armour."));

    set_money_greed_sell(100);
    set_money_greed_buy(discriminate);
    set_money_greed_change(discriminate);

/*
    config_default_trade();
*/

    set_keeper_file(DUNEDAIN_DIR + "npc/atarauta");

    add_exit(DUNEDAIN_DIR + "rooms/hallw_s", "east", 0, 0);
    add_item(({"floor", "ground", }), BSN(
        "The ground is made from the living rock of the Mindolluin. "
      + "It has been levelled with great care and excellent "
      + "workmanship."));
    add_item(({"wall", "walls", }), BSN(
        "The walls have been carved from the living rock of the "
      + "Mindolluin that have been smoothed and polished with "
      + "great care and by experienced and diligent masons."));
    add_item(({"ceiling", "roof", }), 
        "The roof vaults high above, details cannot be made "
      + "out from down here.\n");
} 

mixed
shop_hook_filter_sell(object x)
{
    if (!weapon_filter(x) && !armour_filter(x))
        return "The shopkeeper says: I do not want your "+x->short()+"!\n"
             + "The shopkeeper says: I do not trade in anything but "
             + "weapons and armours!\n";
    else if (x->id("_dunedain_armour"))
        return 0;
    else if (MASTER_OB(x) == MT_WEAPON)
        return 0;
    else
        return 0;
}

/*
 * Function name:   discriminate
 * Description:     Don't treat all players equal by giving different prices.
 * Returns:         A percentage.   100   pay normal price.
 *                                 >100   annoy player
 *                                 <100   help player
 */
int
discriminate()
{
    object  tp = TP;
    int     bargain = tp->query_skill(SS_TRADING),
            rank    = tp->query_dunadan_level();

    if (bargain > 50) 
        bargain = 50;
    bargain = 100 - (bargain/5);

/*
    if (tp->query_guild_name_race() != GUILD_NAME)
        return (150 * bargain);
*/

    bargain = (bargain * (100 - (rank/4))) / 100;
    return bargain;
}

/*
 * Function name: shop_hook_allow_buy
 * Description:   A hook to use if you want to test the object 
 *		  further if you allow it to be bought
 * Arguments:	  ob - The object player wants to buy.
 * Returns:	  1 if we allow it to be bought (default)
 */
public int
shop_hook_allow_buy(object ob)
{
    object  tp = TP;
    string  house;

    if (ob->id("_dunedain_horn") && 
	strlen(house = ob->query_house()))
    {
	if (TP->query_dunedain_house() != house)
	{
	    keeper->command("say That " + ob->short() + 
                " is an heirloom of the House of " + house +
		".");
	    keeper->command("say I may sell it only to a member of that House.");
	    NF("");
	    return 0;
	}
    }
    return ::shop_hook_allow_buy(ob);
}
