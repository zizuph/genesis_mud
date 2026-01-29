/*
 *  /d/Gondor/guilds/rangers/hq/hq_shop.c
 *
 *  The shop of Ranger Central Headquarters.
 *  - Modified to use Olorin's standard-Gondor-shop, July 1994.
 *  - Modified by Randor 1992
 *  - From the Hobbiton Shop, 1991, by Elessar.
 *
 *  27-Feb-98, Gnadnar: allow players to "show" std equipment,
 *      remove repeated calls to sizeof in loops.
 *  9-July-01, Alto: modified to fit CH theme.
 *  12-Aug-02, Gwyneth: Moved the code into a base shop to be
 *      inherited by all three ranger shops.
 *      The base shop uses a default of the HQ guildhouse settings,
 *      so no more than the inherit is needed.
 */
inherit "/d/Gondor/guilds/rangers/shop_base.c";
#include "../rangers.h"
#include "../shop_items.h"
#include "/d/Gondor/defs.h"

public void
create_ranger_shop()
{
    set_store_room(RANGERS_HQ_DIR + "hq_store");
    set_short("the Central Headquarters Equipment Store");
    set_long("You are in the Central Headquarters Equipment Store. " +
      "There are lots of strange items lying around, probably brought " +
      "here from distant lands. There is a poster on the wall, and " +
      "the exit from the store leads back south.\n");
    set_shop_name("The Central Headquarters Equipment Store");
    set_keeper_file(RANGERS_NPC + "fredegar");
    add_item(({"door"}), "The door is probably leading into the " +
        "storeroom of the shop. The door is standing open, but the shop " +
        "keeper probably would not be amused if you tried to go there.\n");
    add_exit(RANGERS_HQ_DIR + "dcorridor2", "south", 0, 0);

    set_no_sell_prop(({GONDOR_M_RANGERS_NO_SELL, GONDOR_M_ROHIRRIM_NO_SELL,
        GONDOR_M_TIRITH_NO_SELL}));
    set_standard_equip(GONDOR_EQUIP);
}

