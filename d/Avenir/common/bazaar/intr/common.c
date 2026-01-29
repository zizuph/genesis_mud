/*
 * This room contains the common board for all players, mortals as well as
 * immortals. A player who enters this room can only go back to the room
 * he just left, so there are no normal exits from this room.
 *
 * Nick, 921223
 */

inherit "/std/room";
#include "/d/Avenir/common/common.h"
#include <stdproperties.h>

/*
 * Prototypes
 */
void    load_board();

void
create_room()
{
    set_short("In the common board room");

set_long(
      "You stand in a strange room with no windows. Below you is "+
      "a staircase that leads to a noisy room, but here all the "+
      "sounds seem muted and strange. The room is completely empty "+
      "except for a strange bulletin board that stands inexplicably "+
      "in the center of the room.\n");

AE(BAZAAR + "intr/guild","down",0,1);

    set_noshow_obvious(1);

    add_prop(ROOM_I_NO_STEAL, 1);
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
    add_prop(ROOM_I_INSIDE, 1);

    load_board();
}

void
load_board()
{
    object bb;

    seteuid(getuid(this_object()));
    bb = clone_object("/d/Genesis/obj/board");
    bb->move(this_object());
}

void
init()
{
    add_action("back", "back");
    add_action("back", "return");
    add_action("back", "go");

    ::init();
}

int
back(string str)
{
    if (query_verb() == "go" && str != "back")
        return 0;

    this_player()->move_living("back",
                        this_player()->query_prop(LIVE_O_LAST_ROOM));
    return 1;
}

/*
 * Function: enter_inv
 * Description: block non-interactives from entering.
 */
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (living(ob) && !interactive(ob))
        ob->move(from);
}

