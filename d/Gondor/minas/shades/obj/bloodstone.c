inherit "/std/object";
#include <stdproperties.h>

create_object() {
    set_name("bloodstone");
    add_name("stone");
    add_name("jewel");
    set_short("deep red bloodstone");
    set_pshort("deep red bloodstones");
    set_long("This is a very deep red bloodstone. Not a very common stone as it is extremely valueable.\n");
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,14);
    add_prop(OBJ_I_VALUE,1300);
}
