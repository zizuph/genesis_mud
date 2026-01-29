/* gldboard.c: Gladiator board room: Serpine, 4-24-95. */
// Edited a bit to take advantage of my revised board: Shiva, 8-7-95
#pragma save_binary

inherit "/d/Cirath/std/room";
#include "defs.h"
#include <macros.h>

object vote_bucket;

static void
create_board()
{
    object board;
    /*
        if ((board = clone_object(GLAD_ROOM + "shiva_board")))
    */
    if ((board = clone_object("/std/board")))
    {
        board->set_board_name(PSION_LOG+"board");
        board->set_num_notes(50);
        board->set_silent(1);
        board->set_err_log(PSION_LOG+"glad_board_err");
        board->set_show_lvl(0);
        board->set_lock_lvl(0);
        board->set_lock_access(VBFC_ME("may_lock"));
        board->set_unlock_access(VBFC_ME("may_lock"));
        board->move(TO);
    }
    return 0;
}

void
reset_room()
{
    if (!present("board", TO))
        create_board();
    if (QUERY_OVERSEER) return;
 /*   if (!vote_bucket)
    {
        vote_bucket=clone_object(PSION_LOG+"gladvote.c");
        vote_bucket->move(TO);
    }

    vote_bucket->check_over_time(); */
}

create_room()
{
    object board;
    set_short("board room");
    set_long("This is a small cavern dedicated to keeping other informed "+
      "of what is going on in the world. A buletin board floats in the "+
      "middle of the room.\n");

  

    add_exit(PSION_ROOM + "hallway1.c", "west", 0, 1);
    reset_room();
}

int may_lock()
{
    int i;
    i = (QUERY_COUN_MEMB(this_player()->query_real_name()) < 0 &&
      !this_player()->query_wiz_level());
    find_player("luther")->catch_msg(i + "\n");
    return i;
}
