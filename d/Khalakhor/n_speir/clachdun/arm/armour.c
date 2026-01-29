#include "local.h"
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

inherit "/d/Khalakhor/std/armour";

void
create_khalakhor_armour()
{
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(query_ac(), query_at()));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(query_ac()));
    add_prop(CLACHDUN_GUARD_EQUIPMENT, 1);
}
