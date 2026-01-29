
 /* 
    Crab meat leftover.

    Coded by Maniac 24/9/96
 */

inherit "/d/Calia/std/fish_meat";
#include <stdproperties.h>
#include "defs.h"

void
create_fish_meat()
{
    set_name("meat");
    set_pname("meats"); 
    add_name("piece"); 
    set_pname("pieces"); 
    add_adj("crab");

    set_short("piece of crab meat");
    set_pshort("pieces of crab meat");
    set_long("A small piece of crab meat.\n");
    set_amount(50);
    add_prop(OBJ_I_VALUE, 10);
    add_prop(FISH_I_FROM_THALASSIAN_SEA,1);
}

