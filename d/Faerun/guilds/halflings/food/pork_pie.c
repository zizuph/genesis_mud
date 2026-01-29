
/*
 * Food item cloned for halfling guild
 * Finwe, January 2015
 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
 
create_food()
{
    set_name("pie");
    set_adj(({"spiced", "pork"}));
    set_short("spiced pork pie");
    set_long("This is a " + query_short() + ". It is made from small pieces " +
        "of pork and spices. It is baked in a flaky, round pie crust.\n");
    set_amount(75); 
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 60);
}
