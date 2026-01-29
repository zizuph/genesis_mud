/* A slice of cheese. ~solace/puzzle/objects/cheese_slice */

inherit "/std/food";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

#define TYPE	({ "plain", "holey", "crumbly", "rubbery" })
#define COLOUR	({ "white", "red", "blue-speckled", "yellow" })

void create_food()
{
    int ran_type = random(4);
    int ran_colo = random(4);

    set_name("cheese");
    set_adj("slice of");
    add_adj(TYPE[ran_type]);
    add_adj(COLOUR[ran_colo]);
    set_pshort("slices of "+TYPE[ran_type]+" "+COLOUR[ran_colo]+" cheese");
    set_long("A pungent slice of cheese. It looks yummy!\n");

    set_amount(20);

    add_prop(OBJ_I_VALUE, 5);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(HEAP_S_UNIQUE_ID, "cheese_no_"+OB_NUM(TO));
}
