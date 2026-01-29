/* created by Aridor 04/20/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
    set_short("In the air");
    set_long("\n\nYou fall and fall...\n\n");
    
    DARK;
    add_prop(ROOM_I_TYPE, ROOM_IN_AIR);
}

