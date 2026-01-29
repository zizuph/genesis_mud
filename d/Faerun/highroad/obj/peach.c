/*
 * Fruit for the Farms of Faerun
 * Coded by Finwe, October 2006 
 */
 
inherit "/std/food";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
 
create_food()
{
    setuid(); 
    seteuid(getuid());

    set_name("peach");
    add_name("fruit");
    set_adj(({"round", "fuzzy"}));
    set_short("round fuzzy peach");
    set_long("This is a " + short() + ". It is large and round, and is " +
        "pink and yellow colored. On one side of the fruit is a distinctive " +
        "vertical indentation. The fruit is fuzzy and fragrant.\n");
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 60);
}


