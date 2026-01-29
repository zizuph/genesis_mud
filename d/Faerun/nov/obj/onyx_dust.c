inherit "/std/object";

#include <stdproperties.h>

create_object()
{
    set_name("onyx-dust");
     add_name("dust");
    add_name("_onyxd");
    set_adj("black");
    set_short("pinch of black onyx-dust");
    set_pshort("pinches of black onyx-dust");
    set_long("This is a pinch of black dust from an onyx gem.\n");
    add_prop(OBJ_I_VALUE, 80);
    add_prop(OBJ_I_WEIGHT, 100);
}