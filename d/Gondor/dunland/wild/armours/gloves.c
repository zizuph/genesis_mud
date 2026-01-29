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
    set_name("gloves");
    set_short("soft leather gloves");
    set_long("These gloves are made of leather, offering " +
         "very little protection of the hands. Probably " +
         "the maker thought more of comfort than of an " +
         "armourpiece.\n");

    set_adj(({"leather", "soft leather", "soft"}));

    set_at(A_HANDS);

    set_ac(3);
    set_am(({ -1, 1, -1}));

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(18) + random(50));
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 50 + random(100));
}
