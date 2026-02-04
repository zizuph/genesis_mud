
inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("cheese");
    set_adj("round");
    set_long("A large round cheese, made of goat's milk.\n");
    set_amount(300); /* 50 grams of food. */
    add_prop(OBJ_I_WEIGHT, 300); 
    add_prop(OBJ_I_VOLUME, 100);
}
