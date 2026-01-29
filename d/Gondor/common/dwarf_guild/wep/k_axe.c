/*
 * /d/Gondor/common/dwarf_guild/wep/k_axe.c
 *
 * This axe is wielded by the shopkeeper in the shop at the dwarven race
 * guild. It is also used by the bartender.
 *
 * /Mercade 29 july 1993
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

#define WEAPON_HIT 23
#define WEAPON_PEN 29

void
create_weapon()
{
    set_name("axe");

    set_pname("axes");

    set_adj("beautiful");
    add_adj("dwarven");

    set_short("beautiful dwarven axe");
    set_pshort("beautiful dwarven axes");

    set_long(BSN("This axe is a masterpiece, crafted by a skillful smith " +
        "with love for axes and for his profession. Its hard wooden haft " +
        "is lain in with silver and its blade is made of cold steel."));

    add_item( ({ "blade" }),
        BSN("The blade of the " + short() + " is made of steel. It is " +
        "polished to a fine gloss. With a special process of cooling it, " +
        "the blade is made very strong."));
    add_item( ({ "haft", "wooden haft", "hard wooden haft", "hilt", "handle",
 	     "grip", "helve" }),
        BSN("The haft of the " + short() + " is made of wood. It looks " +
        "rather hard and is probably made off oak."));

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_AXE);
    set_dt( (W_SLASH | W_BLUDGEON) );
    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_VALUE, (F_VALUE_WEAPON(WEAPON_HIT, WEAPON_PEN) +
        /* for the beauty! */ 400 + random(151) - 75));
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