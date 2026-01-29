
#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name("the Rhovanion-to-Emerald line");
    add_adj("old");add_adj("smudged");
    set_long("An old, smudged ticket for the seaship out of Rhun.\n");
    add_prop(OBJ_I_VALUE, 20);
}