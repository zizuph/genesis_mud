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

inherit "/std/armour";

void
create_armour()
{

    set_short("brass ring");
    set_long("This is a small brass ring. When you " +
        "look a bit closer you see the name " +
        "Labal stamped on the inside.\n");
    add_name("ring");
    add_adj("brass");
    add_name("_labals_ring");
    set_at(A_ANY_FINGER);
    add_prop(OBJ_I_VOLUME, 5);  // Five cubic centimeter
    add_prop(OBJ_I_WEIGHT, 10);    // Ring weights 10 g
}

