
 /* 
   Turtle meat leftovers by Jaacar 

    Adjusted by Maniac 24/9/96
 */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

void
create_fish_meat()
{
    set_name("meat");
    set_pname("meats"); 
    add_name("slab"); 
    set_pname("slabs"); 
    add_adj("turtle"); 
    set_short("slab of turtle meat");
    set_pshort("slabs of turtle meat");
    set_long("It is a slab of turtle meat about the size of "+
        "a cantelope. It appears to be edible.\n");
    set_amount(250);
    add_prop(OBJ_I_VALUE, 109);
    add_prop(FISH_I_FROM_THALASSIAN_SEA,1);
}

