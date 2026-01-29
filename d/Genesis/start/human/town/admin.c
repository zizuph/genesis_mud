#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "../defs.h"

void
create_room()
{
    object immortal_board;

    set_short("The room for advanced player discussion");
    set_long("The bulletin board that used to occupy this room has fallen " +
        "into disuse and the gnome who used to secure the notes here has " +
	"not been seen in recent years. Some notes still hang by the edges, " +
	"but otherwise it's of no use.\nThe room is kept empty while a new " +
	"use is being deliberated. A bar, maybe?\n");
/*
    set_long("The bulletin board in this room is intended for " +
	     "all \"mature\" discussion between players and wizards. " +
	     "Generally it is refered to as the \"advanced\" board. It " +
             "used to be for \"alternatives for wizardhood\", but now its " +
	     "scope has been widened. This board is not officially " +
             "moderated, but please keep the normal trivialities on the " +
             "Sparkle \"lobby\" board in the room north of here.\n");
 */
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "tower_map.txt");

    add_exit(TOWN_DIR + "tower", "north");
/* Obliterated by Mercade, 1 March 2015.
    immortal_board = clone_object("/std/board");
    immortal_board->set_board_name(TOWN_DIR + "immortal_board_save");
    immortal_board->set_num_notes(50);
    immortal_board->set_anonymous(0);
    immortal_board->set_silent(1);
    immortal_board->set_show_lvl(1);
    immortal_board->move(TO, 1);
  */
}
