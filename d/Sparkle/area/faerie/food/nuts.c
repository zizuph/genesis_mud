/* Wild Nuts for Green Oaks
 * Finwe, March 2005
 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
create_food()
{
    setuid();
    seteuid(getuid());

    set_name("nuts");
    add_name("wild nuts");
    set_adj("basket");
    set_adj("wild");
    set_short("basket of wild nuts");
    set_pshort("baskets of wild nuts");
    set_long("This is a basket of wild nuts gathered from the forest. They " +
        "look healthy and are different shapes and sizes.\n");
    set_amount(60); 
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 60);
}
