/* Mushroom skewer coded by Twire */
inherit "/std/food";
#include <stdproperties.h>
void
create_food()
{
    set_name("skewer");
    set_short("mushroom skewer");
    set_adj("mushroom");
    set_long("A grilled mushroom skewer seasoned with garlic.\n");
    set_amount(20); /* 50 grams of food. */
    add_prop(OBJ_I_WEIGHT, 50); /* Weight */
    add_prop(OBJ_I_VOLUME, 30);
}