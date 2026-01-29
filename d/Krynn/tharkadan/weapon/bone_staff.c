inherit "/std/weapon";
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

void
create_weapon()
{
    set_name("staff");
    add_adj("bone");
    set_short("bone staff");
    set_long("This is a staff carved from the legbone of a subterranean " +
         "umberhulk. While visually impressive and easily swung around " +
         "in combat, you doubt it would be terribly effective at " +
         "dealing damage.\n");

    set_default_weapon(40, 20, W_POLEARM, W_BLUDGEON, W_BOTH);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 1000);
}
