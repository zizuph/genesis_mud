/*
 *
 * Dunlending weapon
 * Coded by Hordak@Genesis
 */

#pragma strict_types

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

void
create_weapon()
{
    seteuid(getuid());


    set_name("spear");
    add_name("polearm");
    set_short("steel-pointed wooden spear");
    set_long("A simple looking spear. A long wooden pole " +
      "with a sharp steel inforced tip. A deadly weapon " +
      "in the right hands. By the look of it, it has " +
      "been made with small resources.\n");

    set_adj(({"steel-pointed", "wooden"}));

    set_hit(35);
    set_pen(35);

    set_wt(W_POLEARM);
    set_dt(W_IMPALE);

    set_hands(W_BOTH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35, 35) + random(100));
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 1200);
}
