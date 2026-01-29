
/*
 * "chosen" object for the Elemental Clerics
 * Someone who has this object has been accepted
 * into the Elemental Clerics but has not completed
 * their joining ceremony yet.
 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

create_object()
{
    set_name("_echosen_");
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_I_NO_STEAL,1);
    set_no_show();
}

string
query_auto_load()
{
    return MASTER + ":";
}
