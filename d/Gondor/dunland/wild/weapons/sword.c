/*
 *
 * Galuks sword
 * Coded by Hordak@Genesis
 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>

void
create_weapon()
{
    set_name("broadsword");
    add_name("sword");
    set_short("sharp steel broadsword");
    set_long("This broadsword must have been well taken care " +
      "of. The handle has been wrapped in leather to make a more " +
      "comfortable grip. It has been made of steel, an alloy between " +
      "iron and carbon. You cannot detect any signs of where it has " +
      "been forged, but from the look of it, the smith did a " +
      "good job.\n");

    set_adj(({"sharp", "steel"}));

    set_hit(32);
    set_pen(28);

    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);

    set_hands(W_ANYH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(32, 28) + random(200));
    add_prop(OBJ_I_WEIGHT, 1800);
    add_prop(OBJ_I_VOLUME, 2200);
}
