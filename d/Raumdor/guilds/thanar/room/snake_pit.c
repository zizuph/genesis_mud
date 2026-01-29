/**********************************************************************
 * - snake_pit.c                                                    - *
 * - Holds the messenger snakes - not open to mortals               - *
 * - Created by Damaris@Genesis 3/2004                              - *
 **********************************************************************/

#include "../guild.h"
#include <stdproperties.h>
inherit GUILD_ROOM;

public void
create_guild_room()
{
    set_short("a snake pit");
    set_long("    This is massive snake pit. Blech.\n");
    add_item(({"room", "area"}), query_long);


    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    add_exit("/d/Raumdor/workroom", "up");


}
