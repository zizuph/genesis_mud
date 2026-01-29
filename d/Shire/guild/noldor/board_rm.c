/*
 * Board room for the Noldor Guild
 * By Finwe, February 1998
 *
 */
 
//#pragma strict_types
 
#include "/d/Shire/sys/defs.h"
#include "noldor.h" 
#include <std.h>

inherit BUILDING_BASE;

static void create_board();

void
create_guild_room()
{
    object board;

    set_short("Noldor discussion room");
    set_long("This is where the Noldor gather to discuss private matters. " +
        "It is large and open to encourage the elves to discuss any " +
        "topic they desire. A bulletin board dominates the room holding " +
        "many notes relating to the matters they have discussed and " +
        "reports of what is happening outside the valley.\n");
    set_extra_wall(" A large window is set in the north wall " +
        "filling the room with @@daylight_desc@@.\n");

    set_extra_window("The windows are set into the north wall.");
    add_item(({"north window", "northern window"}),
         "The valley spreads to the north and up to the mountains.\n");

    add_exit(NOLGLD_DIR + "foyer", "south");
    add_exit(NOLGLD_DIR + "rest_rm", "east");
    add_exit(NOLGLD_DIR + "med_rm", "west");

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

    if ((board = clone_object("/d/Shire/std/board")))
    {
        board->set_board_name(NOLGLD_DIR + "board");
        board->set_num_notes(30);
        board->set_silent(1);
        board->set_show_lvl(0);
        board->set_remove_rank(WIZ_NORMAL);
        board->set_remove_str("You may not do that.\n");
        board->move(TO);
    }
    return 0;
}
