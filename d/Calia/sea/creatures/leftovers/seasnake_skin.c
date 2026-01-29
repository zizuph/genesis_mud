
 /* Seasnake skin leftovers by Jaacar */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

create_fish_meat()
{
    set_name("skin");
    add_name("seasnake skin");
    add_name("snake skin");
    set_short("seasnake skin");
    set_long("It is a white and black striped strip of seasnake skin.  Perhaps it could "+
        "be good for making something out of.\n");
    set_amount(150);
    add_prop(OBJ_I_VALUE, 42);
    add_prop(FISH_I_FROM_THALASSIAN_SEA,1);
}
