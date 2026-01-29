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
    set_name("grapefruit");
    set_adj(({ "large", "pink"}));
    set_short( "large grapefruit");
    set_long( "It is a plump juicy grapefruit.\n");
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 110);
    add_prop(OBJ_I_VOLUME,  60);
}
