inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 12

void
create_armour()
{
    set_name("fur");
    set_pname("furs");

    set_adj("smelly");

    set_short("smelly fur");
    set_long("What creature this thick mass of furs came from, " +
      "you do not know, but what you do know, is that " +
      "whatever it was, it smelt!\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
}
