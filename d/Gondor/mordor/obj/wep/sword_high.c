/*
 * This is a scimitar (sword) used by orcs in the tower at Cirith Ungol.
 * (It comes in three sizes: high, medium and low; this is high.)
 *
 * /Mercade, 28 july 1993
 */

inherit "/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/formulas.h"
#include "/d/Gondor/defs.h"

#define WEAPON_HIT 30
#define WEAPON_PEN 40

void
create_weapon()
{
    set_name("longsword");
    add_name("sword");
    add_name("weapon");

    set_adj("steel");
    set_adj("black");

    set_short("black steel longsword");
    set_pshort("black steel longsword");

    set_long(BSN("This longsword is made by orcs. Its blade is forged is a " +
        "strange way, which made it black. It looks very strong and is " +
        "probably a very good weapon."));

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_SWORD);
    set_dt( (W_SLASH | W_IMPALE) );
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WEAPON_HIT, WEAPON_PEN) +
        random(201) - 100);
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
