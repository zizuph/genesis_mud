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
    set_short("pair of oars");
    set_long("This is a pair of oars typically used " +
             "to row a small boat.\n");
    add_name(({"_oars","_pair_of_oars","oars","pair of oars"}));
    add_prop(OBJ_I_VOLUME, 500);  // Fifty cubic centimeter
    add_prop(OBJ_I_WEIGHT, 500);    // Oars weights 0.5 Kg
}
