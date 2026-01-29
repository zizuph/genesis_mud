/*
 * Fruit from Garden
 * Coded by Finwe, February 1998
 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"
 
 
create_food()
{
    set_name("peach");
    set_adj("fuzzy");
    set_adj("ripe");
    set_short("fuzzy ripe peach");
    set_long("A large, juicy ripe. It is as large as a big " +
        "apple and ready to be eaten.\n");
    add_name("fruit");
    set_amount(75); 
    add_prop(OBJ_I_WEIGHT, 130);
    add_prop(OBJ_I_VOLUME, 75);
}
