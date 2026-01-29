inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("boots");
    set_ac(20);
    set_at(A_FEET);
    add_adj("steel");
     set_long("A pair of steel boots, they are bulky but they seem to fit.\n");
    set_short("pair of steel boots");
    set_pshort("pairs of steel boots");
    add_prop(OBJ_I_VOLUME, 1750);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_LEGS));
    /*should be A_FEET but that results in 0!*/
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20));
}

