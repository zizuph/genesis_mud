/* 
 * Food for the Party area
 * Finwe, october 2017
 */
inherit "/std/food";

#include <stdproperties.h>

#define ADJ1    "frosted"
#define ADJ2    "vanilla"
#define FOOD    "cupcake"

void
create_food()
{
    set_name(FOOD);
    set_adj(({ADJ1, ADJ2}));
    set_short(ADJ1 + " " + ADJ2 + " " + FOOD);
    set_long("This is a " + query_short() + ". It smells delicious, and is " +
        "frosted with chocolate icing. Colored sugars are sprinkled across " +
        "the top of it.\n");
    set_amount(75);
    add_prop(HEAP_I_UNIT_WEIGHT, 70);
    add_prop(HEAP_I_UNIT_VOLUME, 70);
   
    add_prop(HEAP_S_UNIQUE_ID,"_party_vanilla_cupcake");
}
