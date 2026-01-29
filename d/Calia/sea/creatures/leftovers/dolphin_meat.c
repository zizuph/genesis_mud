
 /* Dolphin meat leftovers by Jaacar */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

create_fish_meat()
{
    set_name("meat");
    add_name("dolphin meat");
    set_short("strip of dolphin meat");
    set_pshort("strips of dolphin meat");
    set_long("It is a small strip of dolphin meat.  It looks edible.\n");
    set_amount(350);
    add_prop(OBJ_I_VALUE, 209);
    add_prop(FISH_I_FROM_THALASSIAN_SEA,1);
}
