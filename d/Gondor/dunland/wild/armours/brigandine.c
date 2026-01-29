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
    set_name("brigandine");
    set_short("hardened leather brigandine");
    set_long("This brigandine is made of cloth. Although the cloth " +
      "is completely covered with small squares of hardened " +
      "leather. Each square has been carefully sewn to the " +
      "cloth. The back of the brigandine has leather straps " +
      "so the armour can be adjusted to fit perfectly. The " +
      "armour has no arms, and it stretches down over the " +
      "waist, hanging loose in ribbons over the thighs.\n");

    set_adj(({"leather", "hardened leather", "hardened"}));

    set_at(A_BODY);

    set_ac(30 + random(5));
    set_am(({ -1, 1, -1}));

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30) + random(25));
    add_prop(OBJ_I_VOLUME, 1400);
    add_prop(OBJ_I_WEIGHT, 1000 + random(100));
}
