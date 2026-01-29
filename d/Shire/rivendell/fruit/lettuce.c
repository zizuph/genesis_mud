/*
 * Vegetables from Garden
 * Coded by Finwe, February 1998
 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"
 
 
create_food()
{
    set_name("lettuce");
    set_adj(({"large", "fresh"}));
    set_short("large fresh head of lettuce");
    set_long("A large fresh head of lettuce. This lettuce is " +
        "amazing. The leaves are large and the head is the size " +
        "of a pumpkin. Surely this will satisfy any hunger.\n");
    add_name("vegetable");
    set_amount(500);  
    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 500);
}                             
