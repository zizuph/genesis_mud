inherit "/std/container";
#include "/d/Kalad/defs.h"
void
create_container()
{
    set_name("purse");
    set_adj("black");
    add_adj("leather");
    set_long("This is a purse made of fine black leather.\n");
    add_prop(CONT_I_WEIGHT,500);
    add_prop(CONT_I_MAX_WEIGHT,1000);
    add_prop(CONT_I_VOLUME,500);
    add_prop(CONT_I_MAX_VOLUME,2000);
}

