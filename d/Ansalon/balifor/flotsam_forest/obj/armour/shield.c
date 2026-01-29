inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 20

void
create_armour()
{
    set_name("shield");
    set_pname("shields");
    add_name("armour");
    add_pname("armours");

    set_adj("large");
    add_adj("oaken");

    set_short("large oaken shield");
    set_pshort("large oaken shields");
    set_long("This very large shield has been skillfully " +
      "crafted from the ancient oak trees of the Goodlund " +
      "forests. Due to some form of treatment, it is " +
      "a deep brown colour. You would gather it would be " +
      "a decent shield, even though it is rather heavy.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_SHIELD);

    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
}
