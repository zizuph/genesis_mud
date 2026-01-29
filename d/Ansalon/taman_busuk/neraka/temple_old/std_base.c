/* The temple base.
 */

#pragma strict_types

#include "defs.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include <stdproperties.h>

inherit AR_FILE
inherit TEMPLE + "std_block";

#define CREATE  "create_temple_room"
#define RESET   "reset_temple_room"

nomask public int
query_reset()
{
    return !(!(function_exists(RESET, this_object())));
}

nomask public void
create_krynn_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    call_other(this_object(), CREATE);
}
