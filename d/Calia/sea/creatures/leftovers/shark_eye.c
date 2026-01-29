
 /* Shark eye leftovers by Jaacar */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

create_fish_meat()
{
    set_name("eyeball");
    add_name("shark eyeball");
    add_pname("shark eyeballs");
    add_name("eye");
    add_pname("eyes");
    set_short("shark eyeball");
    set_long("It's an eyeball from a great white shark.\n");
    set_amount(100);
    add_prop(OBJ_I_VALUE, 21);
    add_prop(FISH_I_FROM_THALASSIAN_SEA,1);
}
