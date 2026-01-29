
 /* Dolphin flipper leftovers by Jaacar */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

create_fish_meat()
{
    set_name("flipper");
    add_name("dolphin flipper");
    set_short("dolphin flipper");
    set_long("It is a grey coloured flipper from a dolphin.\n");
    set_amount(325);
    add_prop(OBJ_I_VALUE, 181);
    add_prop(FISH_I_FROM_THALASSIAN_SEA,1);
}
