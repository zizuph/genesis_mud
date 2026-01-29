/*
 * /d/Gondor/mordor/obj/wep/tool_axe.c
 *
 * This axe is a tool that is used by orcs to chop wood. In fact, it is a
 * weapon, which is obvious.
 *
 * /Mercade 29 july 1993
 */

inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

/*
 * I know that those values are illegal if you apply the rules utterly
 * strictly. However, you will have to kill a 95 and a 55 orc in order to
 * access the axe, so I think I can get away with it.
 */
#define WEAPON_HIT 15
#define WEAPON_PEN  7

void
create_weapon()
{
    set_name("axe");
    add_name("tool");
    add_name("_tool_axe_at_cirith_ungol_");

    set_adj("tool");
    set_adj("wooden");

    set_short("wooden tool axe");
    set_pshort("wooden tool axes");

    set_long(BSN("It is a wooden axe, used to chop trees. It is designed " +
        "especially for that purpose, but it can also be used on living " +
        "creatures. However, that may not help you as much as you expect " +
        "it to help you."));

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_AXE);
    set_dt( (W_SLASH | W_BLUDGEON) );
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VOLUME, 3000);
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
