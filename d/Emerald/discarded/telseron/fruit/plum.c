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
    set_name("plum");
    set_adj(({ "dark", "juicy"}));
    set_short("large ripe plum");
    set_long("It's a large, ripe, purple plum. You just know your " +
        "fingers are going to be messy when you're done eating it.\n"); 
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME,  60);
}
