/*  file:  /d/Calia/sea/objects/rotten_fish.c
 *  description:  This rotten fish looks like the product
 *    of a contaminated area by the cliff where osprey lives. It is
 *    provided as a food item to give to osprey chick.
 */

inherit "/d/Calia/std/fish_meat";
inherit "/d/Calia/std/owner"; 
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_fish_meat()
{
    set_name("fish");
    set_pname("fish"); 
    set_adj("slightly rotten");
    set_long("A slightly rotten little fish.\n");
    set_amount(1); /* 1 gram of food. */
    add_prop(HEAP_I_UNIT_WEIGHT, 25); 
    add_prop(HEAP_I_UNIT_VOLUME, 25);
    add_prop(FISH_I_FROM_THALASSIAN_SEA, 1); 
}

void
hook_smelled()
{
    write("The smell of rotten fish"+
      " assails your nostrils, making you gag.\n");
    say(QCTNAME(this_player()) + " gags.\n");
    return;
}

