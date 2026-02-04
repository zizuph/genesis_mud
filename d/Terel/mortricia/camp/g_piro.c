inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("pirogue");
    set_adj("crunchy");
    set_long("It's a crunchy pirogue. You wonder what it's made of.\n");
    set_amount(5);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 3);
}
