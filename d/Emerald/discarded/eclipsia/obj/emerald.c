inherit "/d/Emerald/std/emgem";
#include <stdproperties.h>

create_emgem()
{
    set_name("emerald");
    set_adj("immaculate");
    set_long("The glittering green emerald is as big as " +
        "your entire palm. This is the fabled Star of Eclipsia. " +
        "The sheer magnitude of the emerald is overwhelming.\n");
    add_prop(OBJ_I_WEIGHT, 350);

    set_gem_value(69120);
}
