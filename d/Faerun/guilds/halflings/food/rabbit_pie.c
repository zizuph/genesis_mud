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
    set_name("pie");
    add_adj( ({"rabbit"}) );
    set_short("rabbit pie");
    set_long("This is a pie made of wild rabbit meat and gravy. The gravy " +
        "has chopped carrots, onions, peas, and savory spices. They have " +
        "been baked into a round pastry crust.\n");
    add_prop(OBJ_I_VALUE, 0);
    set_amount(100);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 60);
}