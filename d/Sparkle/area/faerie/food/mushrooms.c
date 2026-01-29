/* Basket of Mushroom for Green Oaks
 * Finwe, March 2005
 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#define FOOD "mushrooms" 
create_food()
{
    setuid();
    seteuid(getuid());

    set_name(FOOD);
    add_name("basket of " + FOOD);
    set_adj("basket");
    set_adj("large");
    set_short("large basket of " + FOOD);
    set_pshort("large baskets of " + FOOD);
    set_long("This is a large basket of fresh " + FOOD + . They are recently " +
        "harvested and a favorite of elves.\n");
    set_amount(100); 
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 100);
}
