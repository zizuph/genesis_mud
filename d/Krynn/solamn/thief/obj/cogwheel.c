/* created by Aridor, 10/10/94 */

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("cogwheel");
    set_adj("metal");
    add_name("_cogwheel_");
    set_long("This is an ordinary cogwheel with 42 teeth and it is about " +
	     "a foot in diameter.\n");
    add_prop(OBJ_I_VOLUME, 1800);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VALUE, 80);
}
