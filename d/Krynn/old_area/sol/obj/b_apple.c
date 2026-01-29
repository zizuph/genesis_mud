/* The apple the boy under the apple tree has. */

inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("apple");
    set_adj("red");
    add_name("boy_apple");
    set_long("It look very tasty.\n");
    add_prop(OBJ_I_WEIGHT, 180);
    add_prop(OBJ_I_VOLUME, 184);
    set_amount(20);
}

