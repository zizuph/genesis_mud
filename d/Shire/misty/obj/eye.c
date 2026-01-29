inherit "/std/object";
#include <stdproperties.h>

void
create_object()
{
    seteuid(getuid());

    set_name("eye");
    set_pname("eyes");
    set_adj("glass");
    set_long("This is simple glass eye. You have strange feeling that "+
      "it is looking at you.\n");

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 3);
    add_prop(OBJ_I_VALUE, 0);
}
