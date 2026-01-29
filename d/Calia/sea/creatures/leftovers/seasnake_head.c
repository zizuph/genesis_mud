
 /* Seasnake head leftovers by Jaacar */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

create_fish_meat()
{
    set_name("head");
    add_name("seasnake head");
    set_short("seasnake head");
    set_long("It is the head of a large seasnake.\n");
    set_amount(200);
    add_prop(OBJ_I_VALUE, 71);
    add_prop(FISH_I_FROM_THALASSIAN_SEA,1);
}
