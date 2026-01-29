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
    set_name("cherries");
    set_adj("red");
    set_adj("juicy");
    set_short("bunch of juicy cherries");
    set_long("A bunch of deep red juicy cherries. They " +
        "are the largest cherries you have ever seen.\n");
    add_name("fruit");
    set_amount(65); 
    add_prop(OBJ_I_WEIGHT, 125);
    add_prop(OBJ_I_VOLUME, 75);
}                             
