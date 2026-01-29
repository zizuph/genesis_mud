/*
 * Training room of the Wild Elves Guild
 * By Finwe, May 2001
 */
 
#pragma strict_types

#include "../wrunner_defs.h"
#include "/d/Shire/cypress/sys/defs.h"

inherit "/d/Shire/cypress/guilds/wrunner/base_common_inside";

static void create_board();

void
create_room()
{
    object board;

    set_short("An exquisite discussion room");
    set_long("This room is where the Wild Elves gather to " +
        "discuss private things such as travels, news of the " +
        "outside, etc. A large board has been erected here so " +
        "that they may post what they learn and enable others to " +
        "read the news. There are many notes attached to the " +
        "board, some of which you may read. As this is a public " +
        "board, the Wild Elves expect the notes to be written "+
        "in a civilized tone. \n");
    set_add_column_bldg();
    create_board();

    add_exit(ROOM_DIR + "hall",     "west");

}

static void
create_board()
{
    object board;

    if ((board = clone_object("/std/board")))
    {
        board->set_board_name(WRUNNER_DIR + "board");
        board->set_num_notes(30);
        board->set_silent(1);
        board->set_show_lvl(0);
        board->set_remove_rank(this_player()->query_wiz_level());
        board->set_remove_str("You may not do that.\n");
        board->move(TO);
    }
    return 0;
}
