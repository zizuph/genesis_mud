#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

inherit SPIRIT_OBJECTS + "component_base";

public void
create_component()
{
    set_component_type("metaballo");

    set_long("This is the metaballo component used for the "+
        "metaballo gift of the Spirit Circle of Psuchae.\n");
}
