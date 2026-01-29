
 /* Eel meat leftovers by Jaacar */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

create_fish_meat()
{
    set_name("meat");
    add_name("eel meat");
    set_short("strip of eel meat");
    set_pshort("strips of eel meat");
    set_long("It is a small strip of eel meat.  It looks edible.\n");
    set_amount(150);
    add_prop(OBJ_I_VALUE, 42);
    add_prop(FISH_I_FROM_THALASSIAN_SEA,1);
}
