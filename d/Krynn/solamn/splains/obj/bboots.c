inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("boots");
    set_ac(10);
    set_at(A_FEET);
    add_adj("leather");
     set_long("A pair of soft leather boots, they seem to fit you well.\n");
    set_short("pair of leather boots");
    set_pshort("pairs of leather boots");
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(10, A_LEGS));
    /*should be A_FEET but that results in 0!*/
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10));
}

