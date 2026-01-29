/*
 * morning_star.c
 *
 * A simple morning star, no handle, just a chain and
 * spiked ball on the end.
 * 
 * Khail - August 15, 1997
 */
#pragma strict_types

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

#define HIT 24
#define PEN 27

inherit "/d/Khalakhor/std/weapon";
inherit "/lib/keep";

public void
create_khalakhor_weapon()
{
    set_name("morning star");
    add_name("star");
    add_name("chain");
    set_adj("heavy");
   set_short("heavy iron morning star");
   set_pshort("heavy iron morning stars");
    add_adj("iron");
    set_long("This morning star is fairly simply constructed, " +
        "in fact not even a handle is evident, only a long " +
        "chain with a heavy spiked ball at one end.\n");

    set_wt(W_CLUB);
    set_hands(W_ANYH);
    set_dt(W_BLUDGEON | W_IMPALE);
    set_hit(HIT);
    set_pen(PEN);
    set_keep(1);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}
