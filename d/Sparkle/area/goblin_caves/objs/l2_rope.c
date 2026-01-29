/*
 * level 2 quest rope
 * Boreaulam, September 2012
 */
#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "defs.h"

inherit "/std/rope";

void
create_rope()
{
    set_name("rope");
    set_adj("strong");
    set_short("strong rope");
    set_long("This is a long, thick rope which appears to be very strong.\n");
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_VALUE, 30);
}

