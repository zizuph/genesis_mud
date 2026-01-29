
/*
 * potato.c
 * A potato
 * Vegetable merchant
 * Town of Haven
 * Tibbit, 17 February 1998
 *
 */


inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("potato");
    set_adj("big");
    add_adj("brown");

    set_short("big brown potato");
    set_long("Potatoes have long been a Krynnish staple.  "+
        "You hold a particularly fine specimen.\n");

    set_amount(103);

    add_prop(OBJ_I_WEIGHT, 105); /* what does an egg really weight??  */
    add_prop(OBJ_I_VOLUME, 110);
}

