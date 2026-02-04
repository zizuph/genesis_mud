inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>


create_object()
{
    set_name("moonstone");
    set_adj("shimmering");
    set_long(break_string("This looks like a very unusual moonstone " +
	"that's shimmering in all rainbow colors. You wonder where " +
	"it comes from.\n",70));
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 150);
}
