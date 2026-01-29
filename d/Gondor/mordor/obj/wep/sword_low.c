/*
 * This is a scimitar (sword) used by orcs in the tower at Cirith Ungol.
 * (It comes is three sizes: high, medium and low; this is low.)
 *
 * /Mercade, 28 july 1993
 */

inherit "/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/formulas.h"
#include "/d/Gondor/defs.h"

#define WEAPON_HIT 20
#define WEAPON_PEN 15

void
create_weapon()
{
    set_name("scimitar");
    add_name("sword");
    add_name("blade");

    set_adj("iron");

    set_short("iron scimitar");
    set_pshort("iron scimitars");

    set_long(BSN("This scimitar is made by orcs. Its blade is made of iron " +
        "and looks strong. It is probably a very nice weapon."));

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_SWORD);
    set_dt((W_SLASH | W_IMPALE));
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VOLUME, 3500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WEAPON_HIT, WEAPON_PEN) +
        random(101) - 50);
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
