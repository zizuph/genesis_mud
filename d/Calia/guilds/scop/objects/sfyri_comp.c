#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

inherit SPIRIT_OBJECTS + "component_base";

public void
create_component()
{
    set_component_type("sfyri");

    set_long("This is the sfyri component used for the "+
        "sfyri gift of the Spirit Circle of Psuchae.\n");
}
