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

    set_short("small fish");
    set_long("This is a small and very dead fish.\n");
    add_name("fish");
    add_name("_fish");
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 100);    // Fish weights 100 g
    setuid();
    seteuid(getuid());
}

