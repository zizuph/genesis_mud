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
    set_name("carrot");
    set_adj(({"long","crunchy"}));
    set_short("long crunchy carrot");
    set_long("A long, crunchy carrot. It is smooth and and " +
        "looks good enough to satisfy any hunger.\n");
    add_name("vegetable");
    set_amount(65); 
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 150);
}                             
