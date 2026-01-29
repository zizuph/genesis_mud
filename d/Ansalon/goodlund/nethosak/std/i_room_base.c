/* 
 * /d/Ansalon/goodlund/nethosak/std/i_room_base.c
 * 
 * glain
 *
 * This is the indoor base room for all of nethosak.   I just hacked 
 * flotsams i_room_base.c.
 *
 */
#pragma strict_types

#include "/d/Ansalon/common/defs.h"

inherit AR_FILE

#define CREATE "create_nethosak_room"
#define RESET  "reset_nethosak_room"

nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
        return 1;
    return 0;
}

nomask public void
create_krynn_room()
{
    call_other(TO, CREATE);
}

nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}
