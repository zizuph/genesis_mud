/* Pebble for Kender Quest, Gwyneth, 1999 */

inherit "/std/object";
#include <stdproperties.h>

void
create_object()
{
    set_name("pebble");
    set_adj("small");
    add_adj("round");
    set_long("This is a small round pebble, perfect for a slingshot!\n"); 
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
}

