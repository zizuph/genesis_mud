#include "local.h"
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

inherit "/d/Khalakhor/std/armour";

void
create_khalakhor_armour()
{
    set_name("boots");
    set_adj(({"leather","brown","knee-high"}));
    set_short("brown knee-high boots");
    set_long("This "+short()+" are made from a strudy leather which "+
      "has been stained and hardened to provide protection to ones "+
      "legs and feet from slashing attacks.\n");

    set_at(A_FEET | A_LEGS);
    set_ac(12);
    set_am(({-2, 5, -3}));

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(query_ac(), query_at()));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(query_ac()));
    add_prop(CLACHDUN_GUARD_EQUIPMENT, 1);
}
