/* created by Splunge 01/94 */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("helm");
    set_adj(({"red", "plate"}));
    set_ac(16);
    set_at(A_HEAD);
    set_am( ({ -5, 0, 5 }) );
    set_short("red plate helm");
    set_long("It's a large red plate helm.\n");
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(16, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(16));
}
