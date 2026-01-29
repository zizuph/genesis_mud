/*
 *
 * Dunlending armour
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
    set_name("breastplate");
    set_short("dark leather breastplate");
    set_long("This breastplate is made of dark hardened " +
      "leather. You can feel that metal plates has " +
      "been sewn into the armour, reinforcing the " +
      "chest and back area. An impression of a large " +
      "white hand covers the front of the armour.\n");

    set_adj(({"leather", "dark leather", "studded"}));

    set_at(A_BODY);

    set_ac(31 + random(6));
    set_am(({ -1, 1, -1}));

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(31) + random(25));
    add_prop(OBJ_I_VOLUME, 2400);
    add_prop(OBJ_I_WEIGHT, 2000 + random(1000));
}
