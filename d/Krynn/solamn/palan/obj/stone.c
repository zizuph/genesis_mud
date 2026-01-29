/* created by Aridor 07/06/93 */

inherit "/std/object";

#include "../local.h"
#include <stdproperties.h>

create_object()
{
    set_name("stone");
    set_adj("ordinary");
    set_short("ordinary stone");
    set_long(BS("This looks just like any other stone.",SL));
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 30);

}

