
 /* Manta Ray eyeball leftovers by Jaacar */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

create_fish_meat()
{
    set_name("eyeball");
    add_name("manta-ray eyeball");
    add_pname("manta-ray eyeballs");
    add_name("eye");
    add_pname("eyes");
    set_short("manta-ray eyeball");
    set_long("It's an eyeball from a manta-ray.\n");
    set_amount(150);
    add_prop(OBJ_I_VALUE, 42);
    add_prop(FISH_I_FROM_THALASSIAN_SEA,1);
}
