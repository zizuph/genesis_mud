inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

create_object()
{
    set_name("piece of driftwood");
    add_name("driftwood");
    add_name("wood");
    set_pname("pieces of driftwood");
    set_short("old piece of driftwood");
    set_pshort("old pieces of driftwood");
    set_adj("old");
    set_long("It is a piece of driftwood. Maybe it used " +
	     "to be a part of a ship?\n");
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, 1 + random(2));
}
