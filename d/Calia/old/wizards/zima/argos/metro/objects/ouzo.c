/* Ouzo, the "beer"  of Argos */
inherit "/std/drink";
#include <stdproperties.h>
 
create_drink()
{
    set_name("ouzo");
    set_short("ouzo");
    set_long(
       "It is a clear alcoholic drink found in Argos.\n");
    set_soft_amount(100);
    set_alco_amount(5);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 200);
}
