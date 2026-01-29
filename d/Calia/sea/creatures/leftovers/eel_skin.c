
 /* Eel skin leftovers by Jaacar */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

create_fish_meat()
{
    set_name("_eel_skin_");
    add_name("eel skin");
    add_name("skin");
    set_short("eel skin");
    set_long("Its a blue-grey strip of eel skin.  Perhaps it may "+
        "be good for making something out of.\n");
    set_amount(150);
    add_prop(OBJ_I_VALUE, 42);
    add_prop(FISH_I_FROM_THALASSIAN_SEA,1);
}
