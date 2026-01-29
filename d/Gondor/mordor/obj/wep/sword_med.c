/*
 * This is a scimitar (sword) used by orcs in the tower at Cirith Ungol.
 * (It comes in three sizes: high, medium and low; this is medium.)
 *
 * /Mercade, 28 july 1993
 */

inherit "/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/formulas.h"
#include "/d/Gondor/defs.h"

#define WEAPON_HIT 24
#define WEAPON_PEN 28

void
create_weapon()
{
    set_name("broadsword");
    add_name("sword");
    add_name("blade");

    set_adj("curved");
    set_adj("broad");

    set_short("curved broadsword");
    set_pshort("curved broadswords");

    set_long(BSN("This broadsword is made by orcs. Its blade is forged is a " +
        "strange way so that it is curved to do more damage to your victim. " +
        "It looks strong and is probably a good weapon."));

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_SWORD);
    set_dt( (W_SLASH | W_IMPALE) );
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WEAPON_HIT, WEAPON_PEN) +
        random(151) - 75);
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
