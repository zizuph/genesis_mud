inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 22

void
create_armour()
{
    set_name("armour");
    set_adj("leather");

    add_adj("primitive");

    set_short("primitive leather armour");
    set_long("A primitive set of leather armour, with bits " +
      "of steel and other metals attached to it rather crudely, " +
      "but offering a bit more protection from blows than " +
      "a hide armour. It is marked with the emblem of the " +
      "goblins of Blood Mountain.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
}
