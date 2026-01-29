/* Basket of Fresh Berries for Green Oaks
 * Finwe, March 2005
 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#define FOOD "fresh berries"

create_food()
{
    set_name("berries");
    add_name(FOOD);
    add_name("basket of " + FOOD);
    set_pname("baskets of " + FOOD);
    set_short("basket of " + FOOD);
    set_pshort("baskets of " + FOOD);
    set_adj("basket");
    set_adj("fresh");
    set_long("This basket is full of many " + FOOD + ". They were collected " +
        "from the forest and look refreshing.\n");
    set_amount(100);
}
