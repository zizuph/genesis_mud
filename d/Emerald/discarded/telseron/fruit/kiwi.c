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
    set_name("kiwi");
    set_adj(({ "fuzzy", "green"}));
    set_short("large kiwi");
    set_long("It's a large green kiwi fruit. What a delicacy.\n");
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 75);
    add_prop(OBJ_I_VOLUME, 45);
}
