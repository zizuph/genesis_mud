/*
 * /d/Gondor/clubs/storytellers/obj/board.c
 *
 * The storyteller club bulletin board
 *
 */
inherit "/std/board";

#include "../defs.h"

public void
create_board()
{
    seteuid(getuid(this_object()));
    set_long("Storytellers may share information here.\n");
    set_board_name(STORYT_DIR + "board/");
    set_num_notes(40);
    set_silent(1);
    set_show_lvl(1);
    set_no_report(0);
    set_keep_discarded(0);
}
