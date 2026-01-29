
 /* Manta Ray meat leftovers by Jaacar */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

create_fish_meat()
{
    set_name("meat");
    add_name("manta-ray meat");
    set_short("strip of manta-ray meat");
    set_pshort("strips of manta-ray meat");
    set_long("This is a fairly large strip of manta-ray meat.\n");
    set_amount(300);
    add_prop(OBJ_I_VALUE, 155);
    add_prop(FISH_I_FROM_THALASSIAN_SEA,1);
}
