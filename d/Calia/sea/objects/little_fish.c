
/* 
   A little fish, heaps of these appear in the 
   boats of the fishermen in the west Calia water area. 

   Coded by Maniac, 1/8/96, 28/9/96
 */

inherit "/d/Calia/std/fish_meat";
inherit "/d/Calia/std/owner"; 
#include <stdproperties.h>
#include "defs.h"

void
create_fish_meat()
{
    set_name("fish");
    set_pname("fish"); 
    set_adj("little");
    set_long("A little fish.\n");
    set_amount(1); /* 1 gram of food. */
    add_prop(HEAP_I_UNIT_WEIGHT, 25); 
    add_prop(HEAP_I_UNIT_VOLUME, 25);
    add_prop(FISH_I_FROM_THALASSIAN_SEA, 1); 
}


/* Keep the owner name in the new object */ 
void
config_split(int new_num, object orig)
{
    ::config_split(new_num, orig); 
    set_owner(orig->query_owner()); 
}


void
enter_env(object dest, object old)
{
    ::enter_env(dest, old); 
    owned_object_enter(dest, old); 
}

