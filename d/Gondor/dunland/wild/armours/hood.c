/*
 *
 * Dunlending helms
 * Coded by Hordak@Genesis
 */
#pragma strict_types

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

void
create_armour()
{

    set_name("hood");
    set_short("hardened leather hood");
    set_long("This hood is made of hardened leather, and will offer " +
      "quite good protection while still its wearer wont be to " +
      "burdened. You cannot see any signs of where it has been " +
      "created, but it still smells leather, so it must be quite " +
      "recently created. There is an impression of a white hand " +
      "on the top of the hood.\n");

    set_adj(({"hardened leather", "hardened", "leather"}));

    set_at(A_HEAD || A_NECK);

    set_ac(30 + random(3));
    set_am(({ -1, 1, -1}));

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(32) + random(25));
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_WEIGHT, 600);
}
