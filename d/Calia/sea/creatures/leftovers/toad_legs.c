
 /* 

    Toad meat leftover.

    Coded by Jaacar July 2003

  */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

void
create_fish_meat()
{
    set_name("_toad_legs_");
    set_pname("pairs"); 
    add_name("legs");
    add_name("pair");

    add_adj("toad");

    set_short("pair of toad legs"); 
    set_long("A pair of enormous toad legs.\n"); 
    set_pshort("pairs of toad legs"); 

    set_amount(1000);
    add_prop(OBJ_I_VALUE, 21);
    add_prop(FISH_I_FROM_THALASSIAN_SEA, 1);
}

