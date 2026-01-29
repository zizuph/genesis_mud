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

    set_short("iron horseshoe");
    add_name("horseshoe");
    set_long("This is a iron horseshoe. From the looks " +
        "of it, it has never been used by a horse. " +
        "There are many small holes around it, most " +
        "likely for the nails and one little bigger " +
        "hole in the middle.\n");
    add_name("_horseshoe");
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 1000);    // Shoe weights 1000 g

    setuid();
    seteuid(getuid());
}



