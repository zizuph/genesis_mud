inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>


create_object()
{
    set_name("nugget");
    set_adj("gold");
    set_long(break_string("This looks like a small gold " +
	"nugget. There's nothing special about it, it's just quite " +
	"heavy, but might have some value.\n",70));
    add_prop(OBJ_I_VALUE, 1400);
    add_prop(OBJ_I_WEIGHT, 965);
    add_prop(OBJ_I_VOLUME, 50);
}
