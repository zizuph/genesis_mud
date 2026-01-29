/*
 * Food item cloned for halfling guild
 * Finwe, January 2015
 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
 
create_food()
{
    set_name("carrot");
    set_adj("large");
    set_short("large carrot");
    set_long("This is large carrot. It has been freshly dug from the soil, " +
        "and has been cleaned and is ready to be eaten.\n");
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 60);
}
