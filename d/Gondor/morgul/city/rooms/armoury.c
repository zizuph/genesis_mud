/*
 *  Armoury in Minas Morgul
 *  Olorin, July 1994
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/shop.c";
inherit "/d/Gondor/morgul/feeling.c";

#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define STORE_ROOM MORGUL_DIR + "city/rooms/armoury_store"  /* Where the items are stored */

public int
block_keeper()
{
    if (TP == keeper)
        return 1;
    return 0;
}

public void
create_shop()
{
    set_store_room(STORE_ROOM);

    set_long(BSN(
        "You are in Gorzag's Armoury in Minas Morgul. "
      + "It looks rather run-down and sleazy. "
      + "Here you can sell or buy all kind of things at whatever " 
      + "price Gorzag is offering or asking. He has made a poster, "
      + "which you can read if you like. Gorzag will value things "
      + "if you want him to. The exit leading out into Dark Street "
      + "is to the west, and a set of dirty stairs in one corner "
	  + "of the room leads down."));
    set_short("Gorzag's Armoury in Minas Morgul");
    set_shop_name("Gorzag's Armoury");
    set_keeper_file(MORGUL_DIR + "npc/gorzag");
    set_no_sell_prop(GONDOR_M_MORGUL_NO_SELL);

    add_item(({"street","dark street"}), BSN(
        "To the west, you can see narrow Dark Street running from north."));
    add_item(({"stairs","dirty stairs"}), BSN(
        "A set of dirty stairs leads down out of sight. A strange, acrid odor "
	    + "wafts up from the stairs."));

    add_prop(ROOM_I_ALLOW_STEED, 1);

    add_exit(MORGUL_DIR + "city/darkstr0", "west", block_keeper);
	add_exit("/d/Gondor/morgul/city/forge/forge_supplies", "down", block_keeper, 0, 1);

}

void
shop_hook_stolen_item(object pl, object ob)
{
    keeper->command("say Where did you get this " +
        ob->short() + "?");
    keeper->command("glare " + pl->query_real_name());
    keeper->command("say Only soldiers in the Dark Lord's " +
        "army have this kind of equipment!");
    keeper->command("say If you think I'm fool enough to " +
        "buy this, you got the wrong one!");
    keeper->command("say Leave before I call the guards!");
}

void
shop_hook_no_business(object pl)
{
    keeper->command("say I do not want your business, " +
        "you stupid creep!");
    keeper->command("spit " + pl->query_real_name());
    keeper->command("say Leave before I call the guards!");
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
    string race;
    int bargain = tp->query_skill(SS_TRADING);

    if(bargain > 30)
        bargain = 30;
    bargain = 115 - bargain;

    switch(query_feeling(TP))
    {
        case -1: bargain = (bargain *  85) / 100; break;
        case  0: break;
        case  1: bargain = (bargain * 120) / 100; break;
    }
    return bargain;
}

mixed
shop_hook_filter_sell(object x)
{
    if (!weapon_filter(x) && !armour_filter(x))
        return "The shopkeeper says: I do not want your " + x->short() + "!\n" +
               "The shopkeeper says: I do not trade in anything but weapons and armours!\n";
    else
        return 0;
}

