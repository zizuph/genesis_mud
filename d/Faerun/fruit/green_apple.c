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
    set_adj(({"tart", "green"}));
    set_short("tart green apple");
    set_long("It's a tart apple. The skin is a bright green color and smells tart. The apple is round and large.\n");
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 60);
}
