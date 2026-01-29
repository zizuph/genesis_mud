inherit "/std/object";
#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    set_adj("inn");
    set_long("A ticket for the Journey's End Inn.\n");
    add_prop(OBJ_I_VALUE, 120);
}
