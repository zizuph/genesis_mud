/*
 * dummy arrow
 * heap object
 * for Meneldil in N Ithilien
 *
 * not usable as weapon
 *
 * Olorin, April 93
 *
 * Made it less dummy and more real. - Rohim 2002
 */

inherit "/std/arrow";

#include <stdproperties.h>

public void
create_arrow()
{
    set_adj(({ "long", "green-feathered" }));
    set_projectile_id("ith_long_green_feathered_arrow");
    add_prop(HEAP_I_UNIT_WEIGHT, 22);
    add_prop(HEAP_I_UNIT_VOLUME, 26);
    add_prop(HEAP_I_UNIT_VALUE, 12);
    set_hit(36);
    set_pen(32);    
    set_heap_size(1);
}

string
get_projectile_long(string str, object for_obj, int num)
{
    return ((num == 1) ? "This arrow is" : "These arrows are") + 
      " of good quality. Balanced, straight and with " + 
      "fins made from gleaming green feathers.\n";
}





