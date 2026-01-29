/* weapmrch.c: The weapon shop of Tyr. */
inherit "/std/room";
inherit "/d/Genesis/lib/shop";
#include "defs.h"
#include "/d/Cirath/athas/mobber.h"

#define SHOPKEEP "grik"
#define STORE TZ_CARAVAN+"weapstor.c"
#define GONEFISHING !objectp(present(SHOPKEEP, TO))

void
reset_room()
{
    bring_room_mob (SHOPKEEP, TYR_NPCS+"weapdude.c");
}

void
create_room()
{
    set_short("grik's weaponry");
    set_long("With the destruction of Sword Street during the plague-"+
             "spawned riots, Grik was forced to move his shop to Caravan "+
             "Way. Business in the sandstone brick structure has been "+
             "superb, especially after the purchase of Tentavvar, "+
             "who had been sold into slavery for stealing from a noble. "+
             "Archways lead north and east to Caravan Way and Tentavvar's "+
             "workroom, while a massive stone door leads south. A sign "+
             "hangs among various weapons that Grik has for sale.\n");

    add_item(({"door", "stone door"}),
              "Its the thickest door you have ever seen, and made of "+
              "solid stone. You would guess it to be the storeroom.\n");
    add_cmd_item(({"door", "stone door"}),
                 ({"open", "pull", "push"}),
              "Just how strong do you think you are anyway?\n");
    INSIDE
    config_default_trade();
    set_store_room(STORE);

    add_exit(TZ_CARAVAN+"rd_cw_03.c", "north", 0, 1);
    add_exit(TZ_CARAVAN+"bonesmth.c", "east", 0, 1);
    add_exit(STORE, "south", "@@wiz_check", 1);

    reset_room();
}

void init()
{
    ::init();
    init_shop();
}

int shop_hook_allow_sell(object ob)
{
    if (GONEFISHING)
    {
        notify_fail("Sell to who?\n");
        return 0;
    }
    if (weapon_filter(ob)) return 1;
    notify_fail("They only buy weapons here.\n");
    return 0;
}

int shop_hook_allow_buy(object ob)
{
    if (GONEFISHING)
    {
        notify_fail("Nobody seems to be here to sell you anything.\n");
        return 0;
    }
    return 1;
}

void shop_hook_fail_storeroom()
{
    write("You smack solidly into the metal bars.\n");
    say(QCTNAME(this_player())+" slams into the bars with a gong.\n");
}
