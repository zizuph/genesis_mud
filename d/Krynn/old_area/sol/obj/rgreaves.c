/* created by Splunge 01/94 */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("greaves");
    set_adj("plate");
    set_ac(20);
    set_at(A_LEGS);
    set_am( ({ 5, -3, -2 }) );
    set_short("set of red plate greaves");
    set_pshort("set of red plate greaves");
    set_long("A set of red plate greaves, they are made of steel.\n");
    add_prop(OBJ_I_VOLUME, 450);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_LEGS));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20));
}
