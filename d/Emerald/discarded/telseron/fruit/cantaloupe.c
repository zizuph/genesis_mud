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
    set_name("cantalope");
    set_adj(({ "ribbed", "yellow"}));
    set_short( "large cantaloupe");
    set_long( "It's a large ripe cantaloupe. This will surely satisfy " +
        "your appetite.\n"); 
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 150);
}
