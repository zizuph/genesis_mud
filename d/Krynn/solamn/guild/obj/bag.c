inherit "/std/receptacle";

#include "/sys/stdproperties.h"

create_container()
{
    set_name("bag");

    set_long("A normal bag.\n");
    add_prop(CONT_I_WEIGHT,     1000);
    add_prop(CONT_I_MAX_WEIGHT, 10000);
    add_prop(CONT_I_VOLUME,     300);
    add_prop(CONT_I_MAX_VOLUME, 17000);
    add_prop(OBJ_I_VALUE, 12);
    add_prop(CONT_I_CLOSED, 1);
}

