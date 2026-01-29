#include "local.h"
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

inherit "/d/Khalakhor/std/armour";

void
create_khalakhor_armour()
{
    set_name("greaves");
    set_adj(({"silver-laced","plated"}));
    set_short("silver-laced plated greaves");
    set_long("This "+short()+" is made from the finest steel found in "+
      "all of Khalakhor.  A silvery metal has been interwined and "+
      "woven into the greaves for decorative purposes.\n");

    set_ac(38);
    set_at(A_LEGS);
    set_am(({-2, 2, 0}));
    set_likely_break(4);
    set_likely_cond(6);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(query_ac(), query_at()));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(query_ac()));
}
