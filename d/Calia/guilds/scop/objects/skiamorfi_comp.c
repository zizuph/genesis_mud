#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

inherit SPIRIT_OBJECTS + "component_base";

public void
create_component()
{
    set_component_type("skiamorfi");

    set_long("This is the skiamorfi component used for the "+
        "skiamorfi gift of the Spirit Circle of Psuchae.\n");
}
