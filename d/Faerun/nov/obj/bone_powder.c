inherit "/std/object";

#include <stdproperties.h>

create_object()
{
    set_name("bone-powder");
    add_name("_bonep");
    add_name("powder");
    set_adj("white");
    set_short("pinch of white bone-powder");
    set_pshort("pinches of white bone-powder");
    set_long("This is a pinch of white powder grinded from some bone.\n");
    add_prop(OBJ_I_VALUE, 80);
    add_prop(OBJ_I_WEIGHT, 60);
}