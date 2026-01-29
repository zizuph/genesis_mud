/* File         : /d/Khalakhor/guilds/racial/clans/room/start.c
 * Creator      : Tomas@Genesis
 * Copyright:   : Bryan D.
 * Date         : March, 13 2001         
 * Purpose      : Starting room to the default Clans of Khalakhor Guildhome
 * Related Files: /
 * Comments     : This is the Starting room to the default Clansmen guildhome.
 * Modifications: 
 */
#pragma strict_types

#include "defs.h"
#include <stdproperties.h>

inherit GUILD_ROOM;

void
create_guild_room()
{

    set_short("Guest room");
    set_long("The guest room is large enough to house a " +
      "good sized platoon. Several bunk-beds line up on either " +
      "side of the walls. A small sign can be seen nailed " +
      "securely to the wall before you.\n");
    
    add_item(({"bunk-beds", "bunk-bed","bed","beds"}),
      "The beds are plain but better than the cold hard floor.\n");
    add_item(({"walls","wall"}),"The stone walls appear to be quite " +
      "strong. You see nothing special about them.\n");
    add_item(({"platoon"}),"The beds are currently empty.\n");

    add_cmd_item("sign", "read",
             "Members may start their day here by typing: <start here>.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 

    add_exit("hall", "south");
    add_exit("hall_storage", "east");
    add_exit("train", "north");
;
}

int
start(string str)
{
    if (str != "here") 
    {
        notify_fail("Start here?\n");
        return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
        write("You are not a member of "+ GUILD_NAME + "!\n");
        return 1;
    }

    if (this_player()->set_default_start_location(STARTLOC))
    {
        write("Ok.\n");
    }
    else
    {
        write("Sorry, some problem prevents you from starting here.\n");
    }

    return 1;
}

void
init()
{
    ::init();

    add_action(start, "start");
}
