#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

inherit BASE_ARMOUR;

CONSTRUCT_ARMOUR
{
    set_name("helmet");
    set_adj("orc");
    set_short("pointed orc helmet");
    set_long("This is a pointed orc helmet made of steel, inscribed with an emblem of a red claw.\n");
    add_item(({"emblem", "claw", "red claw"}),
	"The emblem is the mark of a tribe of Moria-orcs living in the western "+
	"parts of Moria, also called the Mines of Moria.\n");
    set_ac(16+random(5));
    set_at(A_HEAD);
    set_am( ({ 2, -1, -1}) );
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VALUE,   200);
    add_prop(OBJ_I_VOLUME, 1000);
}

#include "recover"
