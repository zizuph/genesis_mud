/*
 *	/d/Gondor/guilds/bnumen/rooms/hallw_s2.c
 *
 *	Coded by Olorin, November 1994
 *
 * Added a check to load training room to prevent the bug that traps people
 * there, Mar 2002 by Skippern
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/guilds/bnumen/rooms/bnumen_room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/bnumen/lib/bnumen_defs.h"

public void
create_gondor()
{
    set_short("Southern Hallway in the House of the Black Numenoreans");
    set_long(BSN("The hallway has reached a corner here. It continues north "
      + "to the Assembly Hall and west further into the building. "
      + "A doorway opening in the south wall is leading into a vaulted "
      + "chamber."));

    floor(1);
    walls();
    ceiling();

    add_item(({"doorway", "opening", "door", }), BSN(
        "The doorway is leading through the south wall into a vaulted "
      + "chamber. Above the doorway, some letters have been chiselled into "
      + "the stone:")
      + "\t\tSAMBE FINDELION\n");

    add_exit(BNUMEN_DIR + "rooms/hallw_s",    "north", 0,  0);
    add_exit(BNUMEN_DIR + "rooms/train_hall", "south", check_exit,  0);
    add_exit(BNUMEN_DIR + "rooms/hallw_s3",   "west",  check_exit,  0);

    add_prop(ROOM_I_INSIDE, 1);
}

public void
enter_inv(object ob, object from)
{
    string train;

    train = BNUMEN_DIR + "rooms/train_hall";

    ::enter_inv(ob, from);
    train->teleledningsanka();
}

