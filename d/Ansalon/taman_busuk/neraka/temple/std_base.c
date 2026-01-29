/* The temple base.
 */

#pragma strict_types

#include "defs.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include <stdproperties.h>

inherit AR_FILE

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
    int x;
    string *arr = ({ "black", "blue", "green", "red", "white" });

    add_prop(ROOM_I_INSIDE, 1);
    call_other(this_object(), CREATE);

    add_prop(ROOM_I_HIDE, -1);
    add_prop(ROOM_M_NO_SCRY, 1);
    for (x = 0 ; x < sizeof(arr) ; x++)
    {
        if (wildmatch("*/" + arr[x] + "/*", file_name(this_object())))
            remove_prop(ROOM_M_NO_SCRY);
    }
}

nomask public void
reset_krynn_room()
{
    if (query_reset())
    {
        set_searched(0);
        call_other(TO, RESET);
    }
}
