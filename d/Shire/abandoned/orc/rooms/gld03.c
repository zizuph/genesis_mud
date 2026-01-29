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
    add_my_desc("Torches on the wall give some light " +
        "to the tunnel. There is a hole in the north wall. " +
        "The tunnel runs southwest and southeast here.\n");
    add_item(({"torches", "torch"}),
        "The torches are attached to the walls. Some are lit, " +
        "providing a minimum of light to the area while others " +
        "are burnt out.\n");
  
    add_exit(ORCR_ROOM + "tribes", "north");
    add_exit(ORCR_ROOM + "gld02",  "southwest");
    add_exit(ORCR_ROOM + "gld04",  "southeast");

}
