inherit "/std/torch";
#include "/sys/stdproperties.h"

void
create_torch()
{
    set_name("torch");
    set_pname("torches");
    set_adj("small");
    set_long("It's a small torch.\n");
    add_prop(OBJ_I_WEIGHT,300);
    add_prop(OBJ_I_VOLUME,100);
    set_time(150);
    set_strength(1);
    set_short("small torch");
    set_pshort("small torches");
}
