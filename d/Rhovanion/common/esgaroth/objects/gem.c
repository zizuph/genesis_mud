inherit "/std/object";

#include <stdproperties.h>

create_object()
{
    set_name("gem");
    set_adj("cracked");
    set_long("This is a cracked gem, reminiscent of a glory long past.\n");
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_WEIGHT, 20);
}
