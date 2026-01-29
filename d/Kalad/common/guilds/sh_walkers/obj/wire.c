inherit "/std/object";

#include "/d/Kalad/defs.h"

void
create_object()
{
    set_name("_kalad_wire");
    add_name("wire");
    set_adj("long");
    add_adj("thin");
    set_short("piece of long thin wire");
    set_pshort("pieces of long thin wire");
    set_long("This is a long, thin wire. It is strong, as it is made "+
        "of some metallic material. It is very thin, so as to escape "+
        "notice easily.\n");

    add_prop(OBJ_I_WEIGHT,1);
    add_prop(OBJ_I_VOLUME,1);
}

