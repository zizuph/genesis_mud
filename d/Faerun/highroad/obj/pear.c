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
    
    set_name("pear");
    add_name("fruit");
    set_adj(({"large", "heavy"}));
    set_short("large heavy pear");
    set_long("This is a " + short() + ". It has a distinctive bell shape " +
        "and is heavy looking. The skin of the fruit is smooth and is a " +
        "combination of green and yellow.\n");
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 60);

}


