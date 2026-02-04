inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>


create_object()
{
    set_name("gem");
    set_adj("scarlet-red");
    set_long("This is a scarlet-red gem. It looks quite precious.\n");
    add_prop(OBJ_I_VALUE, 2000);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
