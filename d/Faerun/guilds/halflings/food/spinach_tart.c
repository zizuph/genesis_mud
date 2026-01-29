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
    set_name("tart");
    add_adj( ({"spinach"}) );
    set_short("spinach tart");
    set_long("This is a vegetable pie made of chopped spinach and various" +
        "cheeses. It has been flavored with parsley, chervil, and fennel, " +
        "and baked in a flaky crust.\n");
    add_prop(OBJ_I_VALUE, 0);
    set_amount(75);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 60);
}