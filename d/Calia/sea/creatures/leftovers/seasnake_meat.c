
 /* Seasnake meat leftovers by Jaacar */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

create_fish_meat()
{
    set_name("meat");
    add_name("seasnake meat");
    add_name("snake meat");
    set_short("strip of seasnake meat");
    set_pshort("strips of seasnake meat");
    set_long("It is a small strip of seasnake meat.  It looks edible.\n");
    set_amount(200);
    add_prop(OBJ_I_VALUE, 71);
    add_prop(FISH_I_FROM_THALASSIAN_SEA,1);
}
