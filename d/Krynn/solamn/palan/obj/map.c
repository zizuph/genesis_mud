/* created by Aridor 07/06/93 */

inherit "/std/object";

#include "../local.h"
#include <stdproperties.h>

create_object()
{
    set_name("map");
    set_adj("old");
    set_short("old map");
    set_long(BS("This map looks old and used. You can't even "
	+   "read anything on it anymore.",SL));
    add_prop(OBJ_I_VALUE, 5);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 400);

}

