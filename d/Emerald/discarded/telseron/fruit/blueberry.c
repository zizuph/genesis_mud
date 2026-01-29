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
    set_name("blueberry");
    set_adj(({ "large", "plump"}));
    set_short( "handful of blueberries");
    set_long( "They are handful of beautiful blueberries.\n");
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT,  90);
    add_prop(OBJ_I_VOLUME,  45);
}
