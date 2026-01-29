
// A shred of cast iron copied from the Shire dirs for use in
//   the Shire spell melt!
//        -Ilyian May 1995

inherit "/std/object";
inherit "/lib/keep";

#include "/sys/stdproperties.h"

create_object()
{
    set_name(({"_cast_iron", "iron" }));
    set_pname(({"_cast_iron", "iron" }));
    add_name("piece");
    set_short("piece of melted iron");
    set_pshort("pieces of melted iron");
    set_adj("melted");
    set_long(
          "The small piece of cast iron probably came from a tool the "
        + "smith was forging. It probably isn't worth much.\n");

    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VALUE, 2);
}

