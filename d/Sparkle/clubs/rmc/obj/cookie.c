inherit "/std/food";
#include "/sys/stdproperties.h"

create_food()
{
    set_short("small cookie");
    set_name("cookie");
    set_adj("small");
    set_long("This is a small cookie. Looks delicious.\n");
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 100);
    set_amount(100);
}

