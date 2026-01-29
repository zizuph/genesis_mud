inherit "/d/Emerald/std/emgem";
#include <stdproperties.h>

create_emgem()
{
    set_name("pearl");
    set_adj("shining");
    set_long("This shining, creamy white pearl is perfect in " +
        "every way. Without a flaw, the beautiful off-white sphere " +
        "is quite enchanting.\n");
    add_prop(OBJ_I_WEIGHT, 50);

    set_gem_value(1000);
}
