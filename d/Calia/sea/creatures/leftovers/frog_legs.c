
 /* 

    Frog meat leftover.

    Coded by Maniac 24/9/96

  */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

void
create_fish_meat()
{
    set_name("pair");
    set_pname("pairs"); 
    add_name("legs");

    add_adj("frog");

    set_short("pair of frog legs"); 
    set_long("A pair of frog legs.\n"); 
    set_pshort("pairs of frog legs"); 

    set_amount(100);
    add_prop(OBJ_I_VALUE, 21);
    add_prop(FISH_I_FROM_THALASSIAN_SEA, 1);
}

