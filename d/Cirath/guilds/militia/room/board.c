inherit "/std/room";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Cirath/common/defs.h"
#include "../defs.h"

static void
create_board()
{
    object board;
    if((board = clone_object("/std/board")))
    {
     board->set_board_name("/d/Cirath/guilds/militia/room/board");
           board->set_num_notes(50);
        board->set_silent(0);
    board->set_err_log("/d/Cirath/guilds/militia/room/board/errors");
        board->set_show_lvl(0);
        board->move(TO);
    }
    return 0;
}

public void
reset_room()
{
    if(!present("board", TO))
        create_board();
}

void
create_room()
{
    object board;
    set_short("Meeting Hall");
    set_long("This is a big room that is used when the militia must "
    	+"gather and discuss items of importance.  There is a board "
    	+"here where members can place notes about guild issues, or "
    	+"anything for that matter.  Any questions or concerns about "
    	+"the guild as a whole can be posted here and they will be "
    	+"addressed.\n");
    add_exit(MILITIA_ROOM + "m_train","west");
    add_exit(MILITIA_ROOM + "m9","north");
    reset_room();
}

