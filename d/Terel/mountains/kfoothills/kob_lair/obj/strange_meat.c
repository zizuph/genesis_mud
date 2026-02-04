/*
 *  strange_meat.c
 *
 *  Britanica 160322
 */
#pragma strict_types

inherit "/std/food";
#include <stdproperties.h>

/*
 * Function name: create_food
 * Description  : constructor.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_food()
{
    add_name("meat");
    add_name("strange_meat");
    set_short("meat from a strange animal");
    set_pshort("meats from a strange animal");
    set_adj("strange");
    set_long("It's meat from a strange animal.\n");
    set_amount(30);
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 30);
}