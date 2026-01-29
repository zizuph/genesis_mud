inherit "/std/object";

#include "/sys/stdproperties.h"

create_object()
{
    set_name(({"_cast_iron", "iron" }));
    set_pname(({"_cast_iron", "iron" }));
    set_short("shred of cast iron");
    set_pshort("shreds of cast iron");
    set_adj("cast");
    set_long(break_string(
	  "The shred of cast iron probably came from a tool the "
	+ "smith was forging. It probably isn't worth much.\n", 70));

    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VALUE, 2);
}
