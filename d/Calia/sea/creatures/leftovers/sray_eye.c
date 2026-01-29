
 /* Stingray eyeball leftovers by Jaacar */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

create_fish_meat()
{
    set_name("eyeball");
    add_name("stingray eyeball");
    add_pname("stingray eyeballs");
    add_name("eye");
    add_pname("eyes");
    set_short("stingray eyeball");
    set_long("It's an eyeball from a stingray.\n");
    set_amount(150);
    add_prop(OBJ_I_VALUE, 42);
    add_prop(FISH_I_FROM_THALASSIAN_SEA,1);
}
