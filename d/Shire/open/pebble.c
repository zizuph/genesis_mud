#include <stdproperties.h>
inherit "/std/object";


/*
 * Function name: create_object
 * Description:   The standard create routine.
 */
void
create_object()
{
    set_name("pebble");
    set_pname("pebbless");
    set_adj("light-dimming");
    set_long("It's a light-sucking pebble.\n");
    set_short("purple pebble");
    set_pshort("purple pebbles");
    add_prop(OBJ_I_LIGHT, -1);
}
