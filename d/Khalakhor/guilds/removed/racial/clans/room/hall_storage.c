/* File         : /d/Khalakhor/guilds/racial/clans/room/hall_storage.c
 * Creator      : Tomas@Genesis
 * Copyright:   : Bryan D.
 * Date         : March, 13 2001         
 * Purpose      : Storage room to the default Clans of Khalakhor Guildhome
 * Related Files: /
 * Comments     : This is the storage room to the default Clansmen guildhome.
 * Modifications: 
 */
#pragma strict_types

#include "../guild.h"
#include <stdproperties.h>

inherit GUILD_ROOM;

void
create_guild_room()
{

    set_short("Storage room");
    set_long("Just a simple storage room for guests to " +
       "store their gear when not in use.\n");
    
       add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 

    add_exit("start", "west");


}
