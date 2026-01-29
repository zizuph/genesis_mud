#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

inherit SPIRIT_OBJECTS + "component_base";

public void
create_component()
{
    set_component_type("energia");

    set_long("This is the energia component used for the "+
        "energia gift of the Spirit Circle of Psuchae.\n");
}
