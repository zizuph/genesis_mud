
 /* Dolphin eye leftovers by Jaacar */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

create_fish_meat()
{
    set_name("_dolphin_eyeball_");
    add_name("dolphin eyeball");
    add_pname("dolphin eyeballs");
    add_name("eyeball");
    add_name("eye");
    add_pname("eyes");
    add_name("dolphin eye");
    add_pname("dolphin eyes");
    set_short("dolphin eyeball");
    set_long("It's an eyeball from a dolphin.\n");
    set_amount(100);
    add_prop(OBJ_I_VALUE, 21);
    add_prop(FISH_I_FROM_THALASSIAN_SEA,1);
}
