#include "local.h"
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

inherit CREST_ARMOUR;

void
create_crest_armour()
{
    set_name("shield");
    set_adj(({"tower","steel"}));
    set_short("steel tower shield");
    set_long("A massive tower shield made of steel.  This "+short()+
      " would provide excellent protection in combat.\n");
    set_crest_desc(CREST);
    set_crest_id(ID);

    set_at(A_SHIELD);
    set_ac(34);
    set_am(({-1, 1, 0}));

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(34, A_SHIELD));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(CLACHDUN_GUARD_EQUIPMENT, 1);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(34) + 75 + random(125));
}
