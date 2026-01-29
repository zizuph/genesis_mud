/*
 * Board room for Dunedain guild.
 *
 * Olorin, 14-nov-1994
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/dunedain/rooms/dun_room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/dunedain/lib/dunedain_defs.h"

public void
create_gondor()
{
    object  board;

    set_short("a small vaulted room");

    set_long(BSN(
        "This is a small vaulted room next to the large assembly "
      + "hall in the House of the Dunedain in Gondor. On the "
      + "wall opposite to the entrance is a large board on which "
      + "the members of the Houses of the Dunedain can post notes."));

    add_exit(GUILD_DIR + "rooms/hall", "east", 0, 0);

    floor();
    walls();
    ceiling();

    add_prop(ROOM_I_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK,1);

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);

    if (!present("board",TO))
    {
        board = clone_object(GUILD_DIR + "obj/dunedain_board");
        board->move(TO);
    }
}
