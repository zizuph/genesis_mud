inherit "/std/container";
inherit "/lib/keep";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include <wa_types.h>

void
create_container()
{
    set_name("quiver");
    set_adj("leather");
    set_short("leather quiver");
    set_long("This is quiver of leather, used for holding arrows.\n");
    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_VOLUME, 8000);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(CONT_I_MAX_WEIGHT, 10000);
    add_prop(CONT_I_MAX_VOLUME, 10000);
    add_prop(OBJ_M_NO_STEAL, "You can not steal the quiver while it is worn.\n");
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_IS_QUIVER, 1);

    set_keep(1);    
}
