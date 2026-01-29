#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

inherit BASE_ARMOUR;

CONSTRUCT_ARMOUR
{
    set_name("shield");
    set_adj("orc");
    set_short("orc shield");
    set_long("An orc shield made of steel, inscribed with an emblem of a red claw.\n");
    add_item(({"emblem", "claw", "red claw"}),
	"The emblem is the mark of a tribe of Moria-orcs living in the western "+
	"parts of Moria, also called the Mines of Moria.\n");
    set_ac(18);
    set_at(A_SHIELD);
    set_am( ({ 2, -1, -1}) );
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VALUE,   500);
    add_prop(OBJ_I_VOLUME, 2000);
}

#include "recover"

int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY }));
}
