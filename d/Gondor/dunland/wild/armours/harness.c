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
    set_name("harness");
    set_short("hardened leather harness");
    set_long("This armour consist of a ordinary shirt. Sewn " +
      "to it are many small squares of hardened leather. " +
      "They are overlapping eachother, covering every inch " +
      "of the shirt. The shirt is armless, so the armour " +
      "do not offer any protection there. Three leather " +
      "stripes on the side, below the left arm, makes the " +
      "easy to remove and wear.\n");

    set_adj(({"leather", "studded leather", "studded"}));

    set_at(A_BODY);

    set_ac(33 + random(5));
    set_am(({ -1, 1, -1}));

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(35) + random(25));
    add_prop(OBJ_I_VOLUME, 1400);
    add_prop(OBJ_I_WEIGHT, 1000 + random(100));
}
