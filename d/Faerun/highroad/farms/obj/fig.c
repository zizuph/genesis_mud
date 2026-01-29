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
    
    set_name("fig");
    add_name("fruit");
    add_name("_fig_faerun_fruit_");

    set_adj(({"small", "plump"}));
    set_short("small plump fig");
    set_long("This is a " + short() + ". It is bell-shaped with a wide, " +
        "flat bottom narrowing to a pointed top. The top is bent, forming " +
        "a small neck. The fruit is purple colored with slightly wrinkled " +
        "and leathery skin.\n");
    set_amount(30); 
    add_prop(OBJ_I_WEIGHT, 30);
    add_prop(OBJ_I_VOLUME, 60);
}


