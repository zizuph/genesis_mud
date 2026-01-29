#include "local.h"
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

inherit "/d/Khalakhor/std/armour";

void
create_khalakhor_armour()
{
    add_name("boots");
    add_pname("boots");
    set_short("pair of soft leather boots");
    set_pshort("pairs of soft leather boots");
    set_long("These "+short()+" look very worn and "+
      "comfortable.   The leather of these boots "+
      "have been dyed a midnight black colour and have been "+
      "polished to a brilliant shine.\n");

    set_at(A_FEET);
    set_ac(15);
    set_am(({-2, 4, -2}));

    set_likely_cond(20);
    set_likely_break(25);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(query_ac(), query_at()));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(query_ac()));
}
