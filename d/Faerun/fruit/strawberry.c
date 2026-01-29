/*
 * Fruit from Faerun
 * Finwe, November 2015 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
 
create_food()
{
    set_name("strawberry");
    add_name("fruit");
    set_adj(({"large", "sweet"}));
    set_short("large sweet strawberry");
    set_pshort("large sweet strawberries");
    set_long("This is a large sweet strawberry. It is deep red with a green stem.\n");
    set_amount(30); 
    add_prop(OBJ_I_WEIGHT, 57);
    add_prop(OBJ_I_VOLUME, 20);
}
