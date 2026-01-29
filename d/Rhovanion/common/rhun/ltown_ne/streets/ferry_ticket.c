#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>

void create_object()
{
    set_name("ticket");
    add_name("the Rhun ferry line");
    add_adj("fish-smelling");add_adj("old");
    set_long("A ticket for the ferry boat in Rhun.\n");
    add_prop(OBJ_I_VALUE, 2);
}