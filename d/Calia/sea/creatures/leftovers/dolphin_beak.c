
 /* Dolphin beak leftovers by Jaacar */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

create_fish_meat()
{
    set_name("beak");
    add_name("dolphin beak");
    set_short("dolphin beak");
    set_long("This is the beak from a dolphin of the Thalassian "+
        "Sea.  It appears edible.\n");
    set_amount(350);
    add_prop(OBJ_I_VALUE, 209);
    add_prop(FISH_I_FROM_THALASSIAN_SEA,1);
}
