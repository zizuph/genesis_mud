/* glass bottle for black dragon quest by percy */

inherit "/std/object";
#include <stdproperties.h>

int acid;

void
create_object()
{
    set_name("bottle");
        add_name("xaka_bottle");
    set_adj("glass");
        set_short("glass bottle");
        set_long("This is a glass bottle with dragon acid in it.\n");
add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}
