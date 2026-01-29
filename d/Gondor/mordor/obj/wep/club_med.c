/*
 * This is an orc club, used by the orcs in the tower at Cirith Ungol.
 * (It comes in three sizes: high, medium and low; this is medium.)
 *
 * Unfortunately clubs can only be W_BLUDGEON. Since Quis put a club with
 * W_SLASH in his weapon_guide, I am not worried about this club with W_IMPALE.
 *
 * /Mercade, 28 july 1993
 */

inherit "/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

#define WEAPON_HIT 30
#define WEAPON_PEN 20

void
create_weapon()
{
    set_name("club");

    set_adj("orc");
    set_adj("orcish");
    set_adj("wooden");
    set_adj("spiked");

    set_short("spiked orc club");
    set_pshort("spiked orc clubs");
    set_long(BSN("An orcish club, made of a hard type of wood. On the top " +
        "of the club are many iron spikes to mutilate your victim even more " +
        "than with blunt strokes alone."));
    add_item( ({ "spikes", "iron spikes" }), BSN("On the orcish club you " +
        "see many spikes. These spikes are made of iron and look mean. " +
        "Hitting late your victim with this weapon will hurt him more than " +
        "with blunt strokes alone."));

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_CLUB);
    set_dt( (W_BLUDGEON | W_IMPALE) );
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 6000);
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
