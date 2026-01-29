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
    set_name("nectarine");
    set_adj(({ "smooth", "golden"}));
    set_short( "golden ripe nectarine");
    set_long( "This sun-ripened fruit is a nectarine. Not as fuzzy " +
        "as a peach but just as good and juicy.\n"); 
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME,  60);
}
