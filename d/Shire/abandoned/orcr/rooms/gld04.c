/*
* Orc Racial Guild 
* These rooms have light in them.
* By Finwe, October 2000
*/

#pragma strict_types

inherit "/d/Shire/std/room.c";
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

inherit TUNNEL_BASE;

void
create_tunnel_room()
{

    set_long("@@tunnel_desc3@@");
    add_my_desc("Some light comes from the torches on the wall. " +
        "There is a fork in the tunnel here, enabling you to " +
        "go northwest, east, or south.\n");
    add_item(({"torches", "torch"}),
        "The torches are attached to the walls. Some are lit, " +
        "providing a minimum of light to the area while others " +
        "are burnt out.\n");
  
    add_exit(ORCR_ROOM + "gld03", "northwest");
    add_exit(ORCR_ROOM + "gld06", "east");
    add_exit(ORCR_ROOM + "gld05", "south");

}
