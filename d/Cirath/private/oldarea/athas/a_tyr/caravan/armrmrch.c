/* armrmrch.c: Birk the armour merchants shop. */
inherit "/std/room";
inherit "/d/Genesis/lib/shop";
#include "defs.h"
#include "/d/Cirath/athas/mobber.h"

#define SHOPKEEP "birk"
#define STORE TZ_CARAVAN+"armrstor.c"
#define GONEFISHING !objectp(present(SHOPKEEP, TO))

void reset_room()
{
    bring_room_mob (SHOPKEEP, TYR_NPCS+"armrdude.c");
}

void create_room()
{
    set_short("birk's leather and hides");
    set_long ("Thanks to his new location near Caravan Gate, Birk "+
              "has been doing brisk trade in used armour. Now situated "+
              "in a shack across the street from the weapons merchant, "+
              "the armoury has become a favored stop for local and "+
              "traveller alike. Some examples of Birk's work hang on the "+
              "walls, as does a sign. A door north is blocked by thick "+
              "metal bars while Caravan Way is to the south.\n");

    add_item(({"door", "bar", "bars", "metal bars", "metal bar"}),
              "Further proof of Birk's recent success, the bars are made "+
              "of rare steel, and so think that it would take a half-"+
              "giant to lift or bend them. They block the door fully.\n");
    add_cmd_item(({"bar", "bars", "metal bars", "metal bar", "door"}),
                   ({"bend", "lift", "open", "pull", "push"}),
              "Just how strong do you think you are anyway?\n");
    INSIDE
    config_default_trade();
    set_store_room(STORE);

    add_exit(TZ_CARAVAN+"rd_cw_03.c", "south", 0, 1);
    add_exit(STORE, "north", "@@wiz_check", 1);

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
    if (armour_filter(ob)) return 1;
    notify_fail("They only buy armour here.\n");
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
