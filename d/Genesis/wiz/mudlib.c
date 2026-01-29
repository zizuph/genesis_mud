/*
 * /d/Genesis/wiz/mudlib.c
 *
 * This room contains the board for the mudlib discussion.
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
    set_short("the room to discuss mudlib stuff in.");
    set_long("The Mudlib discussion room.\n" +
        BS("This room is specially created to discuss about the mudlib. " +
        "These discussions can be about bugs or about features and ideas.") +
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
        board->set_board_name(name + "/mudlib");
        board->set_num_notes(50);
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
