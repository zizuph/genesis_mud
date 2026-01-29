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
    set_name("grapes");
    set_adj(({ "large", "purple"}));
    set_short( "bunch of grapes");
    set_long( "They are a large bunch of seedless purple grapes.\n");
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME,  65);
}
