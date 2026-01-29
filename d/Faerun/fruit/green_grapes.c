/*
 * Fruit from Faerun
 * Finwe, November 2015 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
 
create_food()
{
    set_name("grapes");
    add_name("fruit");
    set_adj(({"plump", "green"}));
    set_short("cluster of plump green grapes");
    set_pshort("clusters of plump green grapes");
    set_long("This is a cluster of plump green grapes. They are large and sweet looking. The fruit is about the size of your thumb and look ready to fall off the vine.\n");
    set_amount(50); 
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 60);
}
