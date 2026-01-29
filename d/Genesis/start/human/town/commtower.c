/*
 * /d/Genesis/start/human/town/commtower.c
 *
 * Place where mortals post suggestions to the wizzes
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <std.h>

#include "../defs.h"
#include "tower.h"

static object fix_board();

void
create_room()
{
    object ob;

    set_short("In the tower of realms");

    set_long("This is an annex to the Tower of Realms. Cursive writing " +
	     "on the wall makes it clear that this room is intended for mortals " +
	     "who wish to suggest improvements on the world to the gods.\n");

    add_prop(ROOM_S_MAP_FILE, "tower_map.txt");
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 1);

    if (!(ob = fix_board()))
        write("Board could not be created");
    else
        add_my_desc("Next to the door is a bulletin board. " +
        "It is intended for constructive criticism and suggestions to " +
        "the wizard population. Abuse of this board will be punished!\n");

    add_exit(TOWN_DIR + "tower", "east");
}

object
fix_board()
{
    object sugg;

    sugg = clone_object("/std/board");
    if (sugg) {
        sugg->set_board_name("/d/Genesis/start/human/town/sugg_save");
        sugg->set_num_notes(90);
        sugg->set_anonymous(0);
        sugg->set_silent(1);
        sugg->set_show_lvl(1);
	sugg->set_remove_rank(4);
        sugg->set_remove_str("Sorry, mortals are not allowed to remove notes.");
	sugg->set_err_log("/d/Genesis/start/human/town/sugg_err");

	sugg->move(this_object());
	return sugg;
    }
    return 0;
}
