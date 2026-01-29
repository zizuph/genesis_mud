/* created by Splunge 01/94 */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("armour");
    add_name("plate");
    set_ac(30);
    set_at(A_BODY);
    add_adj( ({ "red", "plate" }) );
    set_long("It's a body armour plated with red scales.\n");
    add_prop(OBJ_I_VOLUME, 3040);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(30, A_BODY));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30));
}
