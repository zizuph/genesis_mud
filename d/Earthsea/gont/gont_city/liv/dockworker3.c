#pragma strict_types

inherit "/d/Earthsea/gont/gont_city/liv/dockworker";

#include "defs.h"

public void
create_dockworker()
{
    set_levels(5);
    add_equipment(({ ARM + "breeches", ARM + "iron_ringmail",
        WEP + "cutlass" }));
}
