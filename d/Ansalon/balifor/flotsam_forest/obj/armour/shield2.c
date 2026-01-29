inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 25

void
create_armour()
{
    set_name("shield");

    set_adj("heavy");
    add_adj("steel");

    set_short("heavy steel shield");
    set_long("This is a large heavy shield made of steel.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_SHIELD);

    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
}
