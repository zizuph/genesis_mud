/*
 * /d/Gondor/common/dwarf_guild/wep/pick_axe.c
 *
 * It is the pick-axe that is sold by the smith in the Dwarven race guild.
 *
 * /Mercade 7 January 1994
 *
 * Revision history:
 */

#pragma save_binary

inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"
#include "../dwarf.h"

#define WEAPON_HIT 14
#define WEAPON_PEN 26

void
create_weapon()
{
    set_name("axe");
    add_name("pickaxe");
    add_name("pick-axe");

    set_pname("axes");
    add_pname("pickaxes");
    add_pname("pick-axes");

    add_adj("iron");
    add_adj("dwarven");
    add_adj("strong");
    add_adj("pick");

    set_short("strong pick-axe");
    set_pshort("strong pick-axes");

    set_long(BSN("It is a strong pick-axe with a rather thick haft and a " +
        "steel blade. It can be use for mining purposes, though you can " +
        "also try to hack your opponents neck with it."));

    add_item( ({ "haft", "helve", "handle", "grip", "hilt" }),
        BSN("The haft of this pick-axe is rather thick in order to get " +
        "a good grip on it."));
    add_item( ({ "blade", "steel blade" }),
        BSN("The blade of the pick-axe is made of steel. It is rather " +
        "strong and designed to hack rock with."));

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_AXE);
    set_dt( (W_SLASH | W_BLUDGEON) );
    set_hands(W_BOTH);
    set_likely_break(5);
    set_likely_dull(5);

    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WEAPON_HIT, WEAPON_PEN) + 50);
    add_prop(OBJ_S_WIZINFO,
	BSN("This pick-axe was sold (and crafted) by Borin, smith in the " +
	DWARVEN_RACE_GUILD_NAME + ". It can be used in various quests " +
	"or used in order to mine at locations that were previously (read: " +
	"by wizards) selected. /Mercade"));
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}