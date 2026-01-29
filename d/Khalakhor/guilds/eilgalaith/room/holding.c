/**********************************************************************
 * - holding.c                                                      - *
 * -                                                                - *
 * - Created by Damaris@Genesis 04/2007                             - *
 **********************************************************************/
#pragma strict_types

#include "../guild.h"
#include <ss_types.h>
#include <stdproperties.h>
inherit GUILD_ROOM;


public void
create_guild_room()
{

    set_short("darkness");
    set_long("Utter darkness\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("entrance", "back",0,0,1);
}
