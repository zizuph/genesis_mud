/* created by Aridor 07/06/93 */

inherit "/std/object";

#include "../local.h"
#include <stdproperties.h>

create_object()
{
    set_name("feather");
    set_adj("small");
    set_adj("blue");
    set_short("small blue feather");
    set_long(BS("It is definitely a feather. It must have been "
         +   "from some strange bird since it is blue.",SL));
    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 2);
    add_prop(OBJ_I_VOLUME, 40);

}

