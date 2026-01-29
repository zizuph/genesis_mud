/*
 * /d/Gondor/mordor/obj/wep/axe_med.c
 *
 * This is an axe, used by the orcs in the tower at Cirith Ungol.
 * (It comes in three sizes: high, medium and low; this is medium)
 *
 * /Mercade 29 july 1993
 */

inherit "/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

#define WEAPON_HIT 23
#define WEAPON_PEN 29

void
create_weapon()
{
    set_name("axe");

    set_adj("iron");
    set_adj("broad-bladed");

    set_short("broad-bladed iron axe");
    set_pshort("broad-bladed iron axes");

    set_long(BSN("This axe is used by orcs to slay their enemies. Its blade " +
        "is broader than usual and made of iron. Due to its broad blade, it " +
        "will do more damage to your enemy if you hit him."));

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_AXE);
    set_dt( (W_SLASH | W_BLUDGEON) );
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 4000);
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
