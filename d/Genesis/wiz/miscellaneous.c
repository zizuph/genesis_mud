/*
 * /d/Genesis/wiz/miscellaneous.c
 *
 * This room contains the board for miscellaneous discussion.
 *
 * /Mercade
 *
 * Revision history:
 */

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>

#define BS(x) break_string(x, 75)
object board;
string name;

void
create_room()
{
    set_short("the room for miscellaneous discussion");
    set_long("The miscellaneous discussion room.\n" +
        BS("This room is specially created to discuss all kinds of things " +
        "that are not Genesis related. The topic is free, though please " +
	"keep the discussion civilized. Remember we also have a flame board " +
	"in another room.") +
        "\n");

    add_prop(ROOM_I_INSIDE,1);
    add_exit("@@start_location", "start", 0);
    add_exit("/d/Genesis/wiz/virtual", "virtual", 0);
    if (!present("board",this_object()))
    {
        board = clone_object("/std/board");
        name = "/d/Genesis/wiz/boards";
        if (file_size(name) != -2)
            mkdir(name);
        board->set_board_name(name + "/miscellaneous");
        board->set_num_notes(30);
        board->set_silent(0);
        board->set_show_lvl(1);
        board->set_remove_lvl(30);
        board->set_remove_str("Nope, you cannot remove that note.");
        board->move(this_object(), 1);
    }
}

string
start_location()
{
    return (string)this_player()->query_default_start_location();
}
