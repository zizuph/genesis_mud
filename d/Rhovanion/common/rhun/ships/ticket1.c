#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name("the Rhun-to-Esgaroth line");
    add_adj("dirty");add_adj("blue");
    set_long("A ticket for the river-ship in Rhovanion.\n");
    add_prop(OBJ_I_VALUE, 20);
}