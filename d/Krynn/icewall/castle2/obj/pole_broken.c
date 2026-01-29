#pragma strict_types

inherit "/std/object";
#include "/d/Krynn/common/defs.h"
#include <macros.h>


void
create_object()
{

    set_name("pole");
    set_short("A splintered stump of a wooden pole");
    set_long("This is a short, splintered wooden pole. Someone has " +
      "staked it deep into the earth here, but an unknown force has " +
      "snapped it about a meter above the ground. The upper part " +
      "of the pole is nowhere to be seen.\n");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 7000);
    add_prop(OBJ_M_NO_GET, "Only a giant could attempt that!\n");
    add_prop(OBJ_M_NO_STEAL, "It is simply too big...\n");
}
       