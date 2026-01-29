/* -*- Mode: C -*-
 *
 * obj/wep/dagger.c
 *
 * A dagger used by suspect persions.
 */
inherit "/std/weapon";

#include <formulas.h>
#include <wa_types.h>

#define HIT     15
#define PEN     25

void
create_weapon()
{
    set_name("dagger");
    add_name("ArguckAssassinItem");
    set_adj("sharp");
    set_short("sharp dagger");
    set_pshort("sharp daggers");
    set_long("This is a sharp dagger.\n");

    set_hit(HIT);
    set_pen(PEN);

    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);

    set_hands(W_ANYH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + random(40) - 20 );
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, W_KNIFE));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);

    set_wf(this_object());
}
