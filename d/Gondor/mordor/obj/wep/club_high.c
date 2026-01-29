/*
 * This is an orc club, used by the orcs in the tower at Cirith Ungol.
 * (It comes in three sizes: high, medium and low; this is high.)
 *
 * Unfortunately, clubs can only have W_BLUDGEON. Since Quis put a club with
 * W_SLASH in his weapon_guide, I don't worry about it.
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
#define WEAPON_PEN 40

void
create_weapon()
{
    set_name("star");
    add_name("life-preserver");
    add_name("black jack");
    add_name("club");

    set_adj("morning");
    set_adj("orc");
    set_adj("orcish");
    set_adj("heavy");

    set_short("heavy morning star");
    set_pshort("heavy morning stars");
    set_long(BSN("This morning star is sometimes called a life-preserver " +
        "and some people use to refer to it as black jack. It consists of a " +
        "wooden stick with a spiked ball attached to it with a strong " +
        "chain. Swinging this weapon at your opponent, might harm him very " +
        "much if you manage to hit him."));

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_CLUB);
    set_dt( (W_BLUDGEON | W_SLASH) );
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 13000);
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
