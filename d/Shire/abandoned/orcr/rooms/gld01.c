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
    add_my_desc("This is a great cavern carved into the " +
        "mountain. Torches on the walls give some light to the " +
        "cavern. A large poster is attached to a wall near the " +
        "northern entrance. Another entrance leads northeast " +
        "out into the mountain.\n");
    add_item(({"torches", "torch"}),
        "The torches are attached to the walls. Some are lit, " +
        "providing a minimum of light to the area while others " +
        "are burnt out.\n");
    add_item(({"poster", "large poster", "leather poster"}),
        "The poster is made of dried skin. It is white with " +
        "some red splotches on it. It is attached to the wall " +
        "with some wooden stakes. Some crude scribblings are " +
        "written on the poster.\n");
    add_item(({"crude scribblings", "scribblings", "scribbles"}),
        "It is crude looking writing, perhaps done by someone or " +
        "something. Perhaps it can be read.\n");
    /* insert command to read poster */

    add_exit(ORCR_ROOM + "gld02", "north");
    add_exit(ORCR_ROOM + "psg10", "northwest");
}
