#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "../defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>

inherit "/std/object";

void
create_object()
{

    set_short("small wooden plank");
    set_long("This is a small wooden plank. From the " +
        "look you can tell its very old and most likely " +
        "quite rotten inside. Probably totally useless.\n");
    add_name("plank");
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 1000);    // Fish weights 1000 g
}



