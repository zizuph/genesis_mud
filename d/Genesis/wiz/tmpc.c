#pragma save_binary

#include <stdproperties.h>
#include "default.h"

/*
 * Prototypes
 */
void    load_board();

void
create_room()
{
    set_short("In the common board room");
    set_long(break_string(
        "You are standing in a temporarily common room. Here you can " +
	"meet friends and post notes until we find a new site for " +
	"Genesis. There is a post office east and an announcement " +
	"board west." +
        "\n", 70));

    add_exit(THIS_DIR + "tmpp", "east");
    add_exit(THIS_DIR + "tmpd", "west");

    add_prop(ROOM_I_NO_STEAL, 1);
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);

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