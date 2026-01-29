
 /* Fish meat leftovers by Jaacar */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

create_fish_meat()
{
    set_name("meat");
    add_name("fish meat");
    add_name("barracuda meat");
    set_short("strip of fish meat");
    set_pshort("strips of fish meat");
    set_long("It is a small strip of fish meat. It looks edible.\n");
    set_amount(400);
    add_prop(OBJ_I_VALUE, 121);
    add_prop(FISH_I_FROM_THALASSIAN_SEA,1);
}
