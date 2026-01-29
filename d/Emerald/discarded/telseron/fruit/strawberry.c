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
    set_name("strawberry");
    set_adj(({ "large", "plump"}));
    set_short( "large strawberry");
    set_long( "It's a large plump strawberry. Your mouth waters just " +
        "thinking of it.\n");
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT,  80);
    add_prop(OBJ_I_VOLUME,  45);
}
