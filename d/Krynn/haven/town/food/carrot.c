
/*
 * carrot.c
 * A carrot
 * Vegetable merchant
 * Town of Haven
 * Tibbit, 17 February 1998
 *
 */


inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("carrot");
    set_adj("orange");
    add_adj("dull");

    set_short("dull orange carrot");
    set_long("A carrot, dull orange in color, grown "+
        "in the hilly farmland around the town of Haven.\n");

    set_amount(65); /* 65 grams of food. */

    add_prop(OBJ_I_WEIGHT, 65); /* what does an egg really weight??  */
    add_prop(OBJ_I_VOLUME, 25);
}

