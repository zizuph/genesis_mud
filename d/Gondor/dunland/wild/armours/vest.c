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
    set_name("vest");
    set_short("studded leather brigandine");
    set_long("This vest is made of studded leather, ribbons " +
      "woven together, forming a decent protection. The " +
      "shoulders are attached with leather straps on the " +
      "chest, making it fairly easy to remove and wear " +
      "the vest.\n");

    set_adj(({"leather", "studded leather", "studded"}));

    set_at(A_BODY);

    set_ac(29 + random(5));
    set_am(({ -1, 1, -1}));

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(29) + random(25));
    add_prop(OBJ_I_VOLUME, 1400);
    add_prop(OBJ_I_WEIGHT, 1000 + random(100));
}
