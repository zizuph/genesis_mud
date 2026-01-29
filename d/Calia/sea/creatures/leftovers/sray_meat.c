
 /* Stingray meat leftovers by Jaacar */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

create_fish_meat()
{
    set_name("meat");
    add_name("stingray meat");
    set_short("strip of stingray meat");
    set_pshort("strips of stingray meat");
    set_long("This is a fairly large strip of stingray meat.\n");
    set_amount(325);
    add_prop(OBJ_I_VALUE, 181);
    add_prop(FISH_I_FROM_THALASSIAN_SEA,1);
}
