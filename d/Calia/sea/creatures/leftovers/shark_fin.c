
 /* Shark fin leftovers by Jaacar */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

create_fish_meat()
{
    set_name("_shark_fin_");
    add_name("shark fin");
    add_name("fin");
    set_short("shark fin");
    set_long("This is the fin from a great white shark.\n");
    set_amount(400);
    add_prop(OBJ_I_VALUE, 271);
    add_prop(FISH_I_FROM_THALASSIAN_SEA,1);
}
