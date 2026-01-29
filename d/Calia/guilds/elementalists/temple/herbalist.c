/*
 * Herbalist of the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 *
 * Altered payout / cost of herbs to avoid herbstore gaming.
 * Arman - 07 February 2019
 */

#pragma strict_types

#include "defs.h"

inherit TEMPLE_ROOM_BASE;
inherit "/d/Genesis/specials/guilds/lib/storeless_shop";

// Defines

// Prototypes
public string get_sign_instructions();

public int
query_guild_conduit_sell()
{
	return 100;
	/*
    int conduit_level = GUILD_MANAGER->query_guild_conduit();
    switch (conduit_level)
    {
        case 0..33750:
            return 130;
            break;
        case 33751..67500:
            return 95;
            break;
        default:
            return 90;
            break;
    } 
    */ 
}

public int
query_guild_conduit_buy()
{
	return 100;
	/*
    int conduit_level = GUILD_MANAGER->query_guild_conduit();
    switch (conduit_level)
    {
        case 0..33750:
            return 130;
            break;
        case 33751..67500:
            return 95;
            break;
        default:
            return 90;
            break;
    } 
    */ 
}

public void
create_temple_room()
{
    set_short("Inside an herb shop");
    set_long("@@desc_long_description");

    config_default_trade();
    set_money_give_max(50000);
    set_money_give_out(({1000, 5000, 5000, 10}));
    set_money_give_reduce(({4, 0, 20, 15}));
    set_money_greed_buy(query_guild_conduit_buy());
    set_money_greed_sell(query_guild_conduit_sell());
    set_data_filename(ELEMENTALIST_DATA + "herbalist/storeroom");
    
    load_object_data();

    try_item( ({ "small room", "room", "chamber", "herb room" }),
        "From everything you can gather, you're fairly certain that this "
      + "is the Herb Room of the Elemental Temple of Calia.\n");
    
    try_item( ({ "ceiling", "floor", "grey stone", "stone", "polished stone",
                 "polished grey stone", "reflection", "light" }),
        "Both the ceiling and the floor here are made of a smoothly polished "
      + "grey stone. It's a wonder how you can't seem to spot a single "
      + "speck of dust anywhere. The reflection of the light upon the "
      + "polished stone is unblemished by anything.\n");

    try_item( ({ "pungent smell", "smell" }),
        "It's impossible to distinguish the smells from each other as they all "
      + "seem to be blended into each other. Occasionally, your mind tells "
      + "you that you can identify one, but the moment passes quickly.\n");

    
    try_item( ({ "southwest", "temple", "outer circle" }),
        "The exit to the outer circle of the Temple lies to the southwest.\n");

    try_item( ({ "sign", "small sign", "counter" }),
        get_sign_instructions());
    
    add_exit(ELEMENTALIST_TEMPLE + "herb_garden", "northwest", "@@cannot_enter_middle_circle", 1, "@@cannot_see_middle_circle");
    add_exit(ELEMENTALIST_TEMPLE + "outer6", "southwest");
}

/*
 * Function:    init
 * Description: Simple init that calls init_shop, which adds all
 *              the necessary actions in a store.
 */
public void
init()
{
    ::init();
    init_shop();
}

public string
desc_long_description()
{
    string long_desc =
          "This small room seems to be out of place with the rest of the "
        + "Temple. Upon entering this chamber, you can't help but notice the "
        + "pungent smell of herbs as they attack your nostrils. All four "
        + "walls are made of polished wood, the ceiling and floor both a "
        + "smoothly polished grey stone. A simple counter sits in the middle "
        + "of the room. The temple's outer circle lies to the southwest. "
        + "A small sign hangs loosely from the front of the counter.\n\n";

    return long_desc;
}

public string
get_sign_instructions()
{
    return 

        "The small sign reads:\n\n"
        + "\tYou can buy or sell herbs at this herbalist shop.\n"
        + "\tOther possible commands:\n"
        + "\t<list>\t- List what's in stock\n"
        + "\t<value>\t- Allows you to see how much the herbalist will pay for your herbs.\n"; 

}

/*
 * Function name: do_read
 * Description:   If a player wants to know what instuctions can be
 *                used
 * Arguments:     str - string, hopefully "sign"
 * Returns:       1/0
 */
public int
do_read(string str)
{
    notify_fail("Read what?\n");
    if (str != "sign")
	return 0;

    write(get_sign_instructions());
    return 1;
}
