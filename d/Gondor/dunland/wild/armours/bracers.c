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
    set_name("bracers");
    set_short("hardened leather bracers");
    set_long("These bracers covers your lower arms. They " +
      "are very simple, a hardened leather plate attached " +
      "with two leather straps around your arm.\n");

    set_adj(({"leather", "hardened leather", "hardened"}));

    set_at(A_ARMS);

    set_ac(32 + random(4));
    set_am(({ -1, 1, -1}));

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(32) + random(25));
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 350 + random(100));
}
