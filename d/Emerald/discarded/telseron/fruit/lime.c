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
    set_name("lime");
    set_adj(({ "tangy", "ripe"}));
    set_short( "ripe lime");
    set_long( "It is a small ripe lime.\n");
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT,  80);
    add_prop(OBJ_I_VOLUME,  50);
}
