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
    set_name("corn");
    set_adj(({"large", "golden"}));
    set_short("large golden ear of corn");
    set_long("This large golden ear of corn looks sweet. Its " +
        "kernels are large and bursting with flavor.\n");
    add_name("vegetable");
    set_amount(150);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 150);
}                             
