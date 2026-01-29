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
    add_adj( ({"quail"}) );
    set_short("quail egg");
    set_pname("quail eggs");
    set_long("This is a small quail egg. It is beige colored and speckled " +
        "with dark, brown spots. It is hard-boiled and ready to eat.\n");
    add_prop(OBJ_I_VALUE, 0);
    set_amount(75);
    add_prop(OBJ_I_WEIGHT, 43);
    add_prop(OBJ_I_VOLUME, 43);
}