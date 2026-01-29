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
    set_name("apple");
    set_adj("golden");
    set_short("golden apple");
    set_long("It's a large, golden apple. It's perfect in " +
        "every way and was grown by elves.\n");
    add_name("fruit");
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 60);
}
