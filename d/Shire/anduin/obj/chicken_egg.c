/* 
 * Chicken egg from the Woodcutter's chicken coop
 * -- Finwe, November 2005
 */
 
inherit "/std/food";
#include "stdproperties.h"

create_food()
{
    set_name("egg");
    set_short("large chicken egg");
    set_pshort("large chicken eggs");
    set_adj(({"large", "chicken" }));
    set_long("It's a large chicken egg. The egg is smooth and a brownish color.\n");
    set_amount(25);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop("shire_chicken_egg", 1);

}
