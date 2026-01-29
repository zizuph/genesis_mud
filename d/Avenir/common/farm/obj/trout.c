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

    set_short("small trout");
    set_long("This is a fine looking dead trout.\n");
    add_name("trout");
    add_name("_trout");
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 100);    // Trout weights 100 g
    add_prop(OBJ_M_NO_STEAL, 1);
    setuid();
    seteuid(getuid());
}



