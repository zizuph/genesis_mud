inherit "/std/object";

#include <stdproperties.h>

create_object()
{
    set_name("vial");
    add_name("_methyl");
    add_name("dust");
    set_short("tiny vial");
    set_pshort("tiny vials");
    set_long("This is a tiny sealed vial. It is filled with a clear liquid.\n");
    add_prop(OBJ_I_VALUE, 80);
    add_prop(OBJ_I_WEIGHT, 60);
}