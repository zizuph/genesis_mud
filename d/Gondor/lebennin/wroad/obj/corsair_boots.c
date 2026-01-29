/*
 * Leather boots - standard issue boots for corsairs near Linhir
 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
void
create_armour()
{
    set_name("boots");
    set_short("leather boots");
    set_pshort("leather bootses");
    set_long("A pair of sturdy knee-high leather boots.\n");

    set_default_armour(8, A_ANKLES|A_FEET);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(8, A_ANKLES|A_FEET));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}
