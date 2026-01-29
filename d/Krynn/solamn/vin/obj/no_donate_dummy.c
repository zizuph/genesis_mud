
/* This is a dummy for the armoury rack to determine
 * that an object was not donated.
 * made by aridor
 */

inherit "/std/object";
#include "../local.h"
#include "/d/Krynn/common/defs.h"

void
create_object()
{
    set_name("no_donate_dummy");
    set_short("some object");
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
}


