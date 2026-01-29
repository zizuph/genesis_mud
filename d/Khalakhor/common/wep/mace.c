/*
 * mace.c
 *
 * A steel mace. Well crafted, but nothing special.
 * 
 * Khail - August 15, 1997
 */
#pragma strict_types

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

#define HIT 28
#define PEN 20

inherit "/d/Khalakhor/std/weapon";
inherit "/lib/keep";

public void
create_khalakhor_weapon()
{
    set_name("mace");
    add_name("club");
    set_adj("polished");
   set_short("polished steel mace");
   set_pshort("polished steel maces");
    add_adj("steel");
    set_long("The mace is a heavy weapon with a large spherical " +
        "head seated upon a thick wooden haft. The head is edged " +
        "with studs making any impact from it rather painful to " +
        "whoever is on the receiving end.\n");

    set_wt(W_CLUB);
    set_hands(W_ANYH);
    set_dt(W_BLUDGEON);
    set_hit(HIT);
    set_pen(PEN);
    set_keep(1);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}



