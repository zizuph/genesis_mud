inherit "/std/container";

#include <stdproperties.h>

public void
create_container()
{
    set_name("plate");
    set_adj("dinner");

    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_MAX_WEIGHT, 5000);
    add_prop(CONT_I_MAX_VOLUME, 7000);
    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_VOLUME, 700);
}
