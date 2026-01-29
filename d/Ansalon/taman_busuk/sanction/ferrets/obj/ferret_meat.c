/*
 * ferret_meat.c
 * Yummy Ferret Food for Humans
 * 
 * Ares, July 2004
 *
 */

inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("meat");
    set_adj("dried", "ferret");
    set_short("piece of dried ferret meat");
    set_pshort("pieces of ferret meat");
    set_long("The seller of this claims that this tastes "+
    "just like chicken. It doesn't look like chicken. \n");
    add_prop(HEAP_I_UNIT_VALUE,1);
    set_amount(75);
}
