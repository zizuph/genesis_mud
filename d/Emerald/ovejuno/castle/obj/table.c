inherit "/std/container";

#include "../../defs.h"

#include <stdproperties.h>
#include <macros.h>

void
create_container()
{
    if (!IS_CLONE)
    {
        return;
    }

    set_name("table");
    set_adj("oak");
    set_long("An oak table.\n");

    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_WEIGHT, 200000);
    add_prop(CONT_I_VOLUME, 100000);
    add_prop(CONT_I_MAX_WEIGHT, 300000);
    add_prop(CONT_I_MAX_VOLUME, 150000);
    add_prop(OBJ_I_VALUE, 150);

    setuid();
    seteuid(getuid());
    clone_object(CASTLE_OBJ_DIR + "sheet")->move(this_object(), 1);
}
