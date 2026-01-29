
/*
 * celery.c
 * A stalk of celery
 * Vegetable merchant
 * Town of Haven
 * Tibbit, 16 February 1998
 *
 */


inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("celery");
    add_name("stalk");
    set_adj("simple");
    add_adj("celery");
    add_adj("stalk");
    add_adj("of");

    set_short("simple stalk of celery");
    set_long("This simple stalk of celery is probably quite "+
        "nutritious.\n");

    set_amount(50); /* 50 grams of food. */

    add_prop(OBJ_I_WEIGHT, 50); /* what does an egg really weight??  */
    add_prop(OBJ_I_VOLUME, 20);
}

