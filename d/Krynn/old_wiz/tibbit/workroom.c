
/*
 * workroom.c
 * Tibbit's workroom
 * Created 10 Feb 1998 by Tibbit
 *
 */

inherit "/std/room";

#include <stdproperties.h>

object board;

void
create_room()
{
    set_short("Tibbit's workroom");
    set_long("Tibbit's workroom.  It is bare for now.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_exit("/d/Krynn/tibbit/idle","idle");
    add_exit("/d/Krynn/tibbit/rl_work","work");
    add_exit("/d/Krynn/solamn/vin/room/knightroom","kn");
    add_exit("/d/Krynn/solace/new_village/platform1","sol");

    if(!board)
    {
        reset_euid();
        board = clone_object("/std/board");
        board->set_num_notes(20);
        board->set_board_name("/d/Krynn/tibbit/board");
        board->set_no_report(1);
        board->move(this_object());
    }

}

