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
    set_short("simple leather boots");
    set_long("These boots are made of soft leather. The " +
          "are very simple and basic, offering protection " +
          "of the wearers feets during long walks.\n");

    set_adj(({"leather", "soft leather", "soft"}));

    set_at(A_FEET);

    set_ac(5);
    set_am(({ -1, 1, -1}));

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) + random(50));
    add_prop(OBJ_I_VOLUME, 350);
    add_prop(OBJ_I_WEIGHT, 150 + random(100));
}
