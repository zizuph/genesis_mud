/*
 *  The shop in the Black Numenoreans guild
 *
 *  Olorin, 18-nov-1994
 *
 *	Copyright (c) 1994, 1995, 1996 by Christian Markus
 *
 *  TODO:
 *  Add more items to the store room.
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/lib/shop.c";

#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/bnumen/lib/bnumen_defs.h"

#define STORE_ROOM	(BNUMEN_DIR + "rooms/bnumen_store")
#define MT_WEAPON	(MINAS_DIR + "obj/mt_weapon")

public void
create_shop()
{
    set_store_room(STORE_ROOM);

    set_short("the Armoury of the House of the Black Numenoreans");
    set_shop_name("the Armoury of the House of the Black Numenoreans");
    set_long(BSN(
        "This is the Armoury of the House of the Black Numenoreans. Here the "
        + "members of the Houses can buy and sell weapons and armour."));

    set_money_greed_sell(100);
    set_money_greed_buy(discriminate);
    set_money_greed_change(discriminate);

/*
    config_default_trade();
*/

    set_keeper_file(BNUMEN_DIR + "npc/atarauta");

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
    else if (x->id("_bnumen_armour"))
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
            rank    = tp->query_bnumen_level();

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

    if (ob->id("_bnumen_horn") && 
	strlen(house = ob->query_bnumen_house()))
    {
	if (TP->query_bnumen_house() != house)
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
