
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

// I N H E R I T E D   F I L E S
inherit "/std/leftover";

public void 
create_leftover()
{
    set_name("_kurinost_razogh_braid");
    add_name("braid");
    set_adj(({ "soaked","blood-soaked","blood" }));
    set_short("blood-soaked braid");
    set_long("This is the blood-soaked and stinky braid of " +
        "a hobgoblin.\n");

    add_prop(OBJ_I_WEIGHT, 225);
    add_prop(OBJ_I_VOLUME, 55);
    add_prop(OBJ_I_VALUE, 0);
}
