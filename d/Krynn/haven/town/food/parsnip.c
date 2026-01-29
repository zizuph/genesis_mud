
/*
 * parsnip.c
 * A parsnip
 * Vegetable merchant
 * Town of Haven
 * Tibbit, 17 February 1998
 *
 */


inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("parsnip");
    set_adj("light");
    add_adj("beige");

    set_short("light beige parsnip");
    set_long("Parsnips grow well in the hilly "+
        "land surrounding the Krynnish town of Haven.  "+
        "This one is good-sized, and probably good for you, "+
        "although the taste leaves something to be desired.\n");

    set_amount(85); /* 85 grams of food. */

    add_prop(OBJ_I_WEIGHT, 85); /* what does an egg really weight??  */
    add_prop(OBJ_I_VOLUME, 30);
}

