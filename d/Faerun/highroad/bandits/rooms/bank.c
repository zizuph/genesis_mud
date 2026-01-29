/*
 * Bandit bank. Does not store gems.
 * -- Finwe, February 2009
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "/d/Genesis/sys/deposit.h"

inherit BASE_CAVE;
inherit "/lib/bank";

void
create_cave()
{
    object deposit = clone_object("/d/Genesis/obj/deposit");

    deposit->set_bank_id(5202, "Bandit Hideout in Faerun");
    deposit->move(this_object(), 1);
    deposit->set_no_show_composite(1);

    config_default_trade();
    add_item("plaque","@@standard_bank_sign");
    add_cmd_item("plaque","read", "@@standard_bank_sign");

    set_bank_fee(20);

    config_trade_data();

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_ALLOW_STEED,1);
    set_short("a small cave");
    set_long("This cave is south of the shop. The ceiling is low and the walls rough. In the back of the room is a series of iron bound chests. They are used by the thieves to store their money. Periodically a thief comes in and deposits or withdraws some coins from their chest. It seems you may be able to do the same. A plaque hangs on a wall.\n");

    add_item(({"chests", "iron bound chests", "bound chests", "iron chests"}),
        "They are heavy and solid looking, and set along the walls. Although the cave is full of bandits, the chests seem oddly safe from thievery. Each chest is used to store coins by each bandit.\n");

    add_exit(CAVE_DIR + "shop", "north");
}

void
init()
{
    ::init();

    bank_init();
}
