/* Mutton coded by Twire */
inherit "/std/food";
#include <stdproperties.h>
void
create_food()
{
    set_name("mutton");
    set_short("slab of mutton");
    set_adj("slab");
    set_long("This slab of mutton has been seared to perfection.\n");
    set_amount(1750); /* 1.75kgs or 1750 grams of food. */
    add_prop(OBJ_I_WEIGHT, 100); /* Weight */
    add_prop(OBJ_I_VOLUME, 30);
}