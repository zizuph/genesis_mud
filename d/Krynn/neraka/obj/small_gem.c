/*  A small gem */

inherit "/std/object";
#include <stdproperties.h>

void
create_object()
{
    set_name("gem");
    set_adj("small");
    set_long("This gem is very small, but probably still worth " +
	"something.\n");
    add_prop(OBJ_I_VALUE, 123);
}
