/*
 * Board room for Black Numenoreans guild.
 *
 * Olorin, 14-nov-1994
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/guilds/bnumen/rooms/bnumen_room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/bnumen/lib/bnumen_defs.h"

public void
create_cabin()
{
    object  board;

    set_short("a small vaulted cabin");

    set_long("This is a small cabin that houses a board " +
       "on which the members of the houses can post notes.\n");

    add_exit(BNUMEN_DIR + "ship/ncabin_hall3", "port", 0);

    floor();
    walls();
    ceiling();

    add_prop(ROOM_I_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK,1);

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);

    if (!present("board",TO))
    {
        board = clone_object(GUILD_DIR + "obj/bnumen_board");
        board->move(TO);
    }
}
