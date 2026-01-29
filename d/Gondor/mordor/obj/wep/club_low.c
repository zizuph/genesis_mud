/*
 * This is an orc club, used by the orcs in the tower at Cirith Ungol.
 * (It comes in three sizes: high, medium and low; this is low.)
 *
 * /Mercade, 28 july 1993
 */

inherit "/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

#define WEAPON_HIT 15
#define WEAPON_PEN 20

void
create_weapon()
{
    set_name("club");

    set_adj("orc");
    set_adj("orcish");
    set_adj("wooden");
    set_adj("iron");
    set_adj("knobbed");

    set_short("iron knobbed wooden orc club");
    set_pshort("iron knobbed wooden orc clubs");
    set_long(BSN("An orcish club, made of a hard type of wood. On the top " +
        "of the club are some iron knobs to mutilate your victim even more " +
        "than with blunt strokes. These knobs make this club a dangerous " +
        "weapon,"));
    add_item( ({ "knobs", "iron knobs"}), BSN("On the orcish club you see " +
        "several iron knobs to mutilate your victim even more than with " +
        "blunt strokes."));

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 6000);
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
