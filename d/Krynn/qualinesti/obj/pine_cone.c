/*
 * pine_cone.c
 * Pine cone that can be found in Qualinesti.
 *
 * Blizzard, 30/05/2003
 */

#pragma strict_types

inherit "/std/object.c";

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

static int     gDust;

public void
create_object()
{
    set_name(({"pine cone", "cone" }));
    set_short("small brown pine cone");
    set_adj(({ "small", "brown" }));
    set_long("A small brown pine cone. Even if it is considered a fruit, " +
        "it's too hard to be eaten.\n");
    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_M_NO_SELL, 1);
}

