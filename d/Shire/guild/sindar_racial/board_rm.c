#pragma strict_types
 
#include "/d/Shire/sys/defs.h"
#include "sindar_racial.h" 
#include <std.h>

inherit "/d/Shire/std/room";

static void create_board();

void
create_room()
{
    object board;

    set_short("Sindar board room");
    set_long("Write it all down here.\n");

    add_exit(SINDAR_RACE_DIR + "join_rm", "south");

    reset_shire_room();
}

void reset_shire_room()
{
    if (!present("board", TO))
        create_board();
}

static void
create_board()
{
    object board;

    if ((board = clone_object("/std/board")))
    {
        board->set_board_name(SINDAR_RACE_DIR + "board");
        board->set_num_notes(30);
        board->set_silent(1);
        board->set_show_lvl(0);
        board->set_remove_rank(WIZ_NORMAL);
        board->set_remove_str("You may not do that.\n");
        board->move(TO);
    }
    return 0;
}
