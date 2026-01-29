/* 
 * Food item cloned for halfling guild
 * Finwe, January 2016
 */

#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>

public void
create_food()
{
    set_name("egg");
    add_adj( ({"large", "duck"}) );
    set_short("large duck egg");
    set_pname("large duck eggs");
    set_long("This is a large duck egg. It is hard-boiled and redy to eat. " +
        "The egg is oblong shaped and white.\n");
    add_prop(OBJ_I_VALUE, 0);
    set_amount(150);
    add_prop(OBJ_I_WEIGHT, 64);
    add_prop(OBJ_I_VOLUME, 64);
}
