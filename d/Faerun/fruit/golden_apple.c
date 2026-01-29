/*
 * Fruit from Faerun
 * Finwe, November 2015 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
 
create_food()
{
    set_name("apple");
    add_name("fruit");
    set_adj(({"juicy", "golden"}));
    set_short("juicy golden apple");
    set_long("It's a juicy, yellow apple. It's round and smells sweet. The apple is a pale, yellow color with a rosy pink blush color. The bottom of the apple has a couple of bumps.\n");
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 60);
}
