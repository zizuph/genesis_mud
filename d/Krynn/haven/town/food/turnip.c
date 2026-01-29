
/*
 * turnip.c
 * A turnip
 * Vegetable merchant
 * Town of Haven
 * Tibbit, 17 February 1998
 *
 */


inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("turnip");
    set_adj("large");
    add_adj("off-white");
    add_adj("off"); add_adj("white");

    set_short("large off-white turnip");
    set_long("The turnip is a hardy food, often served "+
        "with cheese in a beer sauce.  This one is "+
        "quite large and is colored off-white.\n");

    set_amount(96);

    add_prop(OBJ_I_WEIGHT, 100); /* what does an egg really weight??  */
    add_prop(OBJ_I_VOLUME, 100);
}

