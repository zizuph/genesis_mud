
 /* Turtle eye leftovers by Jaacar 

    Adjusted by Maniac 24/9/96
 */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

void
create_fish_meat()
{
    set_name("eyeball");
    set_pname("eyeballs"); 
    add_adj("turtle");
    set_short("turtle eyeball");
    set_long("It's an eyeball from a turtle.\n");
    set_amount(100);
    add_prop(OBJ_I_VALUE, 21);
    add_prop(FISH_I_FROM_THALASSIAN_SEA,1);
}

