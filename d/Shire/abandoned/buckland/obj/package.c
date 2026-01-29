inherit "/std/object";

#include <stdproperties.h>


void
create_object()
{

    set_name("package");
    add_adj("brown");
    set_short("brown package");
    set_long("A brown package.  It is addressed to ???\n");

    add_prop(OBJ_M_NO_SELL,"You shouldn't sell somebody else's package!\n");
}
