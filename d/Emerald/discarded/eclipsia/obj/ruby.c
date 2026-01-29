inherit "/d/Emerald/std/emgem";
#include <stdproperties.h>

create_emgem()
{
    set_name("ruby");
    set_adj("colossal");
    set_long("This radiant red ruby is must be the largest of its kind. " +
        "Taking a closer look, it looks genuine enough. This must be " +
        "the legendary Heart of Krynn.\n");
    add_prop(OBJ_I_WEIGHT, 350);
    set_gem_value(69120);
}
