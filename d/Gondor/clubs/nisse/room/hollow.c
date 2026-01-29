/*
 *  /d/Gondor/clubs/nisse/room/hollow.c
 *
 *  Private bulletin board room and a start point of the Nisse.
 *
 *  Deagol, April 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include <std.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

/*
 *  Global variables
 */
object	board;

/*
 *  Prototypes
 */
int	exit_out();

public void
create_gondor()
{
    ::create_gondor();

    set_short("The hideout for the Nisse Ohtar");
    set_long("The hollow of the large willow. Even though " +
        "you are standing inside the old willow tree, this place is quite " +
        "spacious and can be used in an emergency as a sanctuary for " +
        "night. There is a cushion made from leaves beneath your feet, and " +
        "there is a fresh herbal scent all around. Breezes in the branches " +
        "make a soft sound making you feel drowsy. A tiny inscription has " +
        "been carved into the wood of this tree. If you want to wake up " +
        "here the next time, type <start here>.\n");

    add_item(({"leaves", "floor", "ground", "cushion"}),
        "There are many leaves lying soft in the hollow as though it were " +
        "a nest. A fresh herbal scent fills the air. You feel it would be " +
        "a very comfortable place to camp. \n");
    add_item(({"inscription", "tiny inscription"}),
        "If you decide to leave the Nisse Ohtar, type <abandon sisterhood> " +
        "here.\n");
    add_item(({"hollow", "place", "inside", "willow tree",
        "old willow tree"}), &long());
    add_item(({"walls", "wall", "ceiling"}),
        "The smooth curved walls and ceiling are carved out from the wood " +
        "inside the old willow tree. They are unadorned except for a board " +
        "that is attached to one side.\n");
    add_item("branches",
        "You can't see the branches from inside the tree, however, you " +
        "can hear the breezes stirring them overhead. It makes a soft " +
        "lullaby sound.\n");

    add_prop(ROOM_I_INSIDE,1);

    FIX_EUID;
    board = clone_object("/std/board");
    board->set_board_name(NISSE_PRIV_BOARD);
    board->set_num_notes(50);
    board->set_silent(0);
    board->set_show_lvl(0);
    board->set_remove_lvl(WIZ_NORMAL);
    board->set_remove_str("The note is firmly affixed to the board.");
    board->move(TO);

    add_exit(NISSE_ROOM_DIR + "o_pool", "out", exit_out, 0, 0);

    clone_object(NISSE_OBJ_DIR + "nisse_admin")->move(TO);
}

/*
 *  Function name: start
 *  Description  : Sets the start point of the player to this room.
 *  Arguments    : string str - as entered by the player
 *  Returns      : 0/1
 */
int
start(string str)
{
    if (!strlen(str) || lower_case(str) != "here")
    {
        notify_fail("Start here?\n");
        return 0;
    }

    if (!TP->query_nisse_level())
    {
        notify_fail("Only the Nisse Ohtar members may sleep here!\n");
        return 0;
    }
    else if (TP->set_default_start_location(NISSE_START))
    {
        write("You will sleep here from now on.\n");
        return 1;
    }
    else
    {
        notify_fail("Some problem prevents you from starting here.\n" +
            "Please make a bug report.\n");
        return 0;
    }
}

/*
 *  Function name: test_exit_out
 *  Description  : Sets in/out message when a player leaves this room.
 *  Returns      : always 1
 */
int
exit_out()
{
    object      player = TP;

    tell_room(NISSE_ROOM_DIR + "o_pool", QCTNAME(player) + " stands " +
        "beside you suddenly.\n");
    player->move_living("M", NISSE_ROOM_DIR + "o_pool", 1, 0);
    tell_room(NISSE_ROOM_DIR + "hollow", QCTNAME(player) + " leaves " +
        "through the hollow.\n");
    return 1;
}

void
init()
{
    ::init();

    add_action(start, "start");
}
