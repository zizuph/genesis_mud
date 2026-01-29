/*
* Orc Racial Guild Start Room
* These rooms have light in them.
* By Finwe, October 2000
*/


#include "/d/Shire/sys/defs.h"
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

inherit TUNNEL_BASE;

void
create_tunnel_room()
{

    set_vbfc_extra(tunnel_desc3);
    extraline = "The cave is carved deep into the mountain. " +
        "Pallets are scattered around the room where tired orcs " +
        "sleep until the next battle. A poster is hammered onto " +
        "the wall above the pallets.\n";
    add_item(({"torches", "torch"}),
        "The torches are attached to the walls. Some are lit, " +
        "providing a minimum of light to the area while others " +
        "are burnt out.\n");
    add_item(({"poster", "large poster", "leather poster"}),
        "The poster is made of dried skin. It is white with " +
        "some red splotches on it. It is attached to the wall " +
        "with some wooden stakes. Some crude scribblings are " +
        "scrawled on it.\n");
    add_item(({"crude scribblings", "scribblings", "scrawls"}),
        "It is crude looking writing, perhaps done by someone or " +
        "something. Perhaps it can be read.\n");
    /* insert command to read poster */
    add_cmd_item("poster", "read", "@@read_poster@@");

    add_exit(ORCR_ROOM + "gld06", "west");

}


init()
{
  ::init();

    add_action("start", "rest");
    add_action("start", "start");
}


string
read_poster()
{
    return "When finished fighting your enemies, you can <start " +
        "here>. Then next time, you shall wake here.\n";
}



start(str)
{
    if(str == "here" && (IS_MEMBER(this_player())))
    {
        TP->set_default_start_location(ORCRGLD_DIR + "start_rm");
        write("You will awaken here when you return.\n");
        return 1;

    }

    write("What? Please try again.\n");
    return 1;
}
