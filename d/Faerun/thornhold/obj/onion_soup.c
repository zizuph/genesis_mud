/* Onion soup coded by Twire */
inherit "/std/food";
#include <stdproperties.h>
void
create_food()
{
    set_name("soup");
    set_adj("onion");
    set_long("A bowl of onion soup smells delicious.\n");
    set_amount(50); /* 50 grams of food. */
    add_prop(OBJ_I_WEIGHT, 50); /* Weight */
    add_prop(OBJ_I_VOLUME, 30);
}