/* spplmrch.c: The general supply store of Tyr. */
inherit "/std/room";
inherit "/d/Genesis/lib/shop";
#include "defs.h"
#include "/d/Cirath/athas/mobber.h"

#define SHOPKEEP "trink"
#define STORE TZ_CARAVAN+"spplstor.c"
#define GONEFISHING !objectp(present(SHOPKEEP, TO))

void
reset_room()
{
    bring_room_mob (SHOPKEEP, TYR_NPCS+"sppldude.c");
}

void
create_room()
{
    set_short("the tarnished cup");
    set_long("Within the large tent hang goods of all sorts, from the "+
             "mundane to the strange. The quality is less than ideal as the "+
             "name of the bazaar, The Tarnished Cup, implies, but at "+
             "least the merchandise is not broken. Caravan Way lies south and a huge "+
             "stone slab rests on what could be tunnel downwards.\n");

    add_item(({"slab", "stone slab"}), "Its a big rock, nothing more.\n");
    add_cmd_item(({"slab", "stone slab"}), ({"lift","move","pull","push"}),
             "Just how strong do you think you are anyway?\n");
    INSIDE
    config_default_trade();
    set_store_room(STORE);

    add_exit(TZ_CARAVAN+"rd_cw_02.c", "south", 0, 1);
    add_exit(STORE, "down", "@@wiz_check", 1);

    reset_room();
}

void
init()
{
    ::init();
    init_shop();
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
        notify_fail("The bizarre doesn't deal in armnament\n");
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

void
shop_hook_fail_storeroom()
{
    write("You stare an the slab a while and decide against it.\n");
    say(QCTNAME(this_player())+" eyes the stone slab longingly.\n");
}
