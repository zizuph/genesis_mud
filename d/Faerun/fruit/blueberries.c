/*
 * Fruit from Faerun
 * Finwe, November 2015 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
 
create_food()
{
    set_name("blueberries");
    add_name("blueberry");
    add_name("fruit");
    set_adj(({"dark", "sweet"}));
    set_short("handful of sweet dark bluberries");
    set_pshort("handfuls of sweet dark bluberries");
    set_long("This is a handful of blueberries. They are dark blue colored and sweet looking.\n");
    set_amount(60); 
    add_prop(OBJ_I_WEIGHT, 227);
    add_prop(OBJ_I_VOLUME, 227);
}
