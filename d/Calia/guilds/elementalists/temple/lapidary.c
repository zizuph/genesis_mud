/*
 * Lapidary of the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 *
 * Added the Avenir shop_list inherit to make it easier
 * to view gems on sale. Also changed the greed for buying
 * and selling, mindful that the gem store clones its own
 * gems.
 * - Arman Kharas February 2019
 */

#pragma strict_types

#include "defs.h"

inherit TEMPLE_ROOM_BASE;
inherit "/lib/shop";
inherit "/d/Genesis/gems/gem_shop";
inherit "/d/Emerald/lib/shop_list";

// Defines
#define GEM_STORAGE     (ELEMENTALIST_TEMPLE + "lapidary_storage")

// Prototypes

public int
query_guild_conduit()
{
    int conduit_level = GUILD_MANAGER->query_guild_conduit();
    switch (conduit_level)
    {
        case 0..33750:
            return 130;
            break;
        case 33751..67500:
            return 120;
            break;
        default:
            return 110;
            break;
    }  
}

public void
create_temple_room()
{
    set_short("Inside the temple lapidary");
    set_long("You stand inside a store which has all kinds of gems. Not "
        + "all of the gems are polished and cut. Some are still embedded "
        + "inside of the earth from which they are found. Behind the "
        + "counter a lapidary clerk is prepared to sell you whatever "
        + "is available in the lapidary. Of course, one can always "
        + "sell gems here as well.\n\n");
 
    setuid();
    seteuid(getuid());
    
    // Create and configure the gem stop
    create_gem_shop();
    this_object()->set_money_greed_buy(100);
    this_object()->set_money_greed_sell(query_guild_conduit());
    set_store_room(GEM_STORAGE);
                      
    add_exit(ELEMENTALIST_TEMPLE + "outer5", "southeast");
    add_exit(ELEMENTALIST_TEMPLE + "gem_garden", "northeast", "@@cannot_enter_middle_circle", 1, "@@cannot_see_middle_circle");
}

public void
init()
{
    ::init();
    init_gem_shop();
}
