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

inherit "/std/container";

void
create_container()
{

    set_short("small metal bucket");
    add_name("bucket");
    add_name("_stable_bucket");
    set_long("This is a small metal bucket used to carry " +
             "oats or water to the horses. It has a small lid " +
             "to prevent anything from spilling out. When " +
             "you lift the lid you find what you expected to find. " +
             "Absolutely nothing at all.\n");
    add_prop(CONT_I_VOLUME, 500);  // Five cubic decimeter
    add_prop(CONT_I_WEIGHT, 1000);    // Bucket weights 1 Kg
    add_prop(CONT_I_MAX_WEIGHT, 10000);
    add_prop(CONT_I_MAX_VOLUME, 5000);
}
