
 /* Shark meat leftovers by Jaacar */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

create_fish_meat()
{
    set_name("meat");
    add_name("shark meat");
    set_short("strip of shark meat");
    set_pshort("strips of shark meat");
    set_long("It is a small strip of shark meat.  It looks edible.\n");
    set_amount(400);
    add_prop(OBJ_I_VALUE, 271);
    add_prop(FISH_I_FROM_THALASSIAN_SEA,1);
}
