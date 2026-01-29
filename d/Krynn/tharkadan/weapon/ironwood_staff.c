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
    add_adj("ironwood");
    set_short("ironwood staff");
    set_long("This is a staff made of the rare wood known as " +
        "ironwood. As hard as normal wood it is incredibly light, " +
        "and is usually only used in the creation of masterwork items. " +
        "This staff has a sharp onyx shard held in place by four " +
        "iron prongs at one end of the staff.\n");

    set_default_weapon(40, 40, W_POLEARM, W_BLUDGEON | W_IMPALE, W_BOTH);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 1000);
}
