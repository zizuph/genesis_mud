/* created by Aridor 07/06/93 */

inherit "/std/object";

#include "../local.h"
#include <stdproperties.h>

create_object()
{
    set_name("feather");
    add_name("pen");
    add_name("pen_feather");
    set_adj("writing");
    set_short("writing feather pen");
    set_long("This looks just like a normal feather, but as you "
	+   "look closer you can see the tip is split a little and "
	+   "there are inkmarks on the feather.\n");
    add_prop(OBJ_I_VALUE, 50);
    add_prop(OBJ_I_WEIGHT, 3);
    add_prop(OBJ_I_VOLUME, 100);

}

