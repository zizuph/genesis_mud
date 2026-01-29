
/*
*    by Amelia for use in the sea area
*    Modifications by Maniac 9/9/96, 3/10/96
*/

inherit "/d/Calia/std/fish_meat";
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

void
create_fish_meat()
{
    set_amount(15);
    set_name("meat");
    set_adj(({"succulent", "oyster"})); 
    set_long("Ah! nothing like wonderful fresh "+
        "seafood, straight from the sea. The oyster "+
        "looks very succulent and is good to eat raw.\n");
    add_prop(FISH_I_FROM_THALASSIAN_SEA, 1); 
}

