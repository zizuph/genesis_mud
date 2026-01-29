#include "local.h"
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

inherit "/d/Khalakhor/std/armour";

void
create_khalakhor_armour()
{
    set_name("coif");
    add_name(({"helmet","helm"}));
    add_adj(({"chain","chainmail","steel"}));
    set_short("chainmail coif");
    set_long("This "+short()+" is make up of tiny links of chain "+
      "weaved together to form a sheet of chainmail which is "+
      "drapped over your head, providing decent protection "+
      "while in combat without limiting your vision.\n");

    set_ac(24);
    set_am(({0,3,-3}));
    set_at(A_HEAD | A_NECK);
    set_likely_break(9);
    set_likely_cond(8);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(query_ac(), query_at()));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(query_ac()));
    add_prop(CLACHDUN_GUARD_EQUIPMENT, 1);
}
