/*
 * Fruit from Garden
 * Coded by Finwe, September 1996
 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
#include "/d/Emerald/defs.h"
 
 
create_food()
{
    set_name("watermelon");
    set_adj("large");
    set_adj("ripe");
    set_short("large seedless watermelon");
    set_long("It's a large, juicy watermelon. This will satisfy " +
        "any appetite.\n");
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 250);
}
