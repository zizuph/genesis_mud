inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>


create_object()
{
    set_name("nugget");
    set_adj("silver");
    set_long(break_string("This looks like a big silver " +
	"nugget. There's nothing special about it, it's just quite " +
	"heavy, but might have some value.\n",70));
    add_prop(OBJ_I_VALUE, 1000);
    add_prop(OBJ_I_WEIGHT, 1575);
    add_prop(OBJ_I_VOLUME, 150);
}
