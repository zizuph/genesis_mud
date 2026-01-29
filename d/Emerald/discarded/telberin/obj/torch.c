
inherit "/std/torch";
inherit "/lib/keep";

#include <stdproperties.h>

void
create_torch()
{
    set_name("torch");
    set_adj("tar-drenched");
    set_short("tar-drenched torch");
    set_long("The torch has been drenched in tar so it can burn for a long "+
             "time.\n");
    set_strength(1);
    set_time(1300);
    set_value(200 + random(5));

    add_prop(OBJ_I_WEIGHT, 1100);
    add_prop(OBJ_I_VOLUME, 950);
    set_keep(1);
}
