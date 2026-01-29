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
    set_name("pants");
    set_short("soft leather pants");
    set_long("These pants are made of leather, and are " +
      "are also reinforced with squares of hardened " +
      "leather sewn to them. The squares covers the " +
      "front of the thighs, the chins and the sides " +
      "of the hip.\n");

    set_adj(({"leather", "soft leather", "soft"}));

    set_at(A_LEGS);

    set_ac(30 + random(4));
    set_am(({ -1, 1, -1}));

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30) + random(25));
    add_prop(OBJ_I_VOLUME, 350);
    add_prop(OBJ_I_WEIGHT, 550 + random(100));
}
