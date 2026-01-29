/*
 * /d/Gondor/mordor/obj/wep/axe_high.c
 *
 * This is an axe, used by the orcs in the tower at Cirith Ungol.
 * (It comes in three sizes: high, medium and low; this is high)
 *
 * /Mercade 29 july 1993
 */

inherit "/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

#define WEAPON_HIT 32
#define WEAPON_PEN 40

void
create_weapon()
{
    set_name("axe");

    set_adj("steel");
    set_adj("black");
    set_adj("sharp");

    set_short("sharp black axe");
    set_pshort("sharp black axes");

    set_long(BSN("This axe is used by orcs to slay their enemies. Its blade " +
        "is made of steel that is forged in a special way to made it black " +
        "yet very sharp. The helve is made of strong wood."));

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_AXE);
    set_dt( (W_SLASH | W_BLUDGEON) );
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 5000);
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
