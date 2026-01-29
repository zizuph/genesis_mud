inherit "/std/room.c";
#include <stdproperties.h>
#include "../defs.h"

object fix_board();

void
create_room()
{
    object ob;
    set_short("Message Board of the Blackhands");
    set_long(break_string(
"You have entered into the middle of a very large hall.  There are lanterns " +
"on the walls here, providing light.  There are various exits leading off to" +
" adjoining rooms.  To the east is a training area, and to the west is the " +
"post office.  The hall continues to the north and south.\n", 78));
    add_prop(ROOM_I_INSIDE, 1);
    if (!(ob = fix_board())) write ("board could not be created");
    else add_my_desc( break_string(
"In the wall near the middle of the room is a bulletin board.  This board " +
"serves the purpose of communication between all members of the " +
"guild.\n", 78));

    add_exit(G_ROOMS + "ghall3", "north", 0);
    add_exit(G_ROOMS + "ghall1", "south", 0);
    add_exit(G_ROOMS + "post", "west", 0);
    add_exit(G_ROOMS + "training", "east", 0);

    add_item(({"lanterns", "lantern"}), break_string(
"They are rusty, smoky, and in great need of more oil.  Unfortuantely for " +
"you, they are firmly attached to the wall.\n", 78));

    add_prop(ROOM_I_INSIDE, 1);

}

object
fix_board()
{
    object thief_bb;
    thief_bb = clone_object("/std/board");
    if (thief_bb) {
        thief_bb->set_board_name(G_ROOMS + "thief_bb_save");
       thief_bb->set_num_notes(30);
       thief_bb->set_anonymous(0);
       thief_bb->set_silent(0);
       thief_bb->set_show_lvl(1);
        thief_bb->set_remove_lvl(50);
       thief_bb->set_remove_string("You don't have the authority to do that.");
       thief_bb->set_err_log(G_ROOMS + "thief_bb_err");
       thief_bb->move(this_object());
       return thief_bb;
    }
    return 0;
}

