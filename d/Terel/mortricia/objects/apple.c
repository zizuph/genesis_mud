inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("apple");
    set_adj("crunchy");
    set_long("It's a crunchy apple. It looks delicious.\n");
    set_amount(3);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 3);
}
