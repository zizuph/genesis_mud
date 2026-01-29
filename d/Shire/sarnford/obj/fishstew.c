#include <stdproperties.h>

inherit "/std/food";

void
create_food() 
{
    set_name(({ "stew", "fish stew" }));
    set_pname(({ "stews", "fish stews" }));
    set_short("fish stew");
    set_pshort("fish stews");
    set_adj("fish");
    set_long("This is fish stew comes from the legendary "
        + "kitchen of the Sleeping Fisherman Inn. Made with assorted "
        + "vegetables and fresh fish caught from the nearby Brandywine "
        + "river, this stew has been spiced just right for even the "
        + "most discriminating palates.\n");
    set_amount(190);
    
    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 350);
    add_prop(OBJ_I_VALUE, 50);
}