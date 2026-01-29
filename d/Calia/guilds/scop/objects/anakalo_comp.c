#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

inherit SPIRIT_OBJECTS + "component_base";

public void
create_component()
{
    set_component_type("anakalo");

    set_long("This is the anakalo component used for the "+
        "anakalo gift of the Spirit Circle of Psuchae.\n");
}
