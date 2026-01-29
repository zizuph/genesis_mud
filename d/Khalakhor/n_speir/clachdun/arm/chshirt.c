#include "local.h"
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

inherit CREST_ARMOUR;

void
create_crest_armour()
{
    set_name("shirt");
    set_adj(({"chain","chain-link","chain-linked","mail"}));
    set_short("chain-link mail shirt");
    set_long("This "+short()+" is made of up many fine "+
      "links of chain, intertwined within each other.  It seems "+
      "that it would offer decent protection in combat deflecting a good "+
      "many blows.\n");

    set_crest_desc(CREST);
    set_crest_id(ID);

    set_at(A_TORSO);
    set_ac(34);
    set_am(({-2,2,0}));
    set_likely_break(6);
    set_likely_cond(8);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(query_ac(), A_TORSO));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
    add_prop(CLACHDUN_GUARD_EQUIPMENT, 1);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(query_ac()));
}
