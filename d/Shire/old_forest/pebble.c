#pragma save_binaries
inherit "/std/object";
 
#include <macros.h>
#include <stdproperties.h>
 
create_object()
{
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,1000);
    add_prop(OBJ_I_VALUE,50);
    set_name(({"pebble","small pebble"}));
    set_short("small pebble");
    set_long("This is a small round pebble. Because of its shape " +
            "it seems to be perfect to throw, or to be " +
            "hurled with the help of a sling, at various targets.\n");
}
 
