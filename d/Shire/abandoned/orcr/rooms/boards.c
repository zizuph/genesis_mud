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
    object board;
    if (!objectp( board) )
    {
        board = clone_object("/std/board");
        board->set_num_notes(30);
        board->set_board_name( "/d/Shire/guild/orcr/board/");
        board->move(this_object());
    }



    set_vbfc_extra(tunnel_desc3);
    extraline = "This tunnel has been expanded into a large " +
        "cave. Some parts of the cave extend into smaller " +
        "caves. A large board dominates one wall.\n";
    add_item(({"torches", "torch"}),
        "The torches are attached to the walls. Some are lit, " +
        "providing a minimum of light to the area while others " +
        "are burnt out.\n");

    add_exit(ORCR_ROOM + "gld07", "south");

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
