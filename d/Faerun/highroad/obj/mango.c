/*
 * Fruit for the Farms of Faerun
 * Coded by Finwe, February 2006 
 */
 
inherit "/std/food";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
 
create_food()
{
    setuid(); 
    seteuid(getuid());
    
    set_name("mango");
    add_name("fruit");
    set_adj(({"large", "smooth"}));
    set_short("large smooth mango");
    set_long("This is a " + short() + ". The fruit is egg shaped and is a " +
        "combination of green, red, and yellow.\n");
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 75);
    add_prop(OBJ_I_VOLUME, 50);
}


