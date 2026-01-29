#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/dunedain/rooms/dun_room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/dunedain/lib/dunedain_defs.h"

public void
create_gondor()
{
    set_short("Southern Hallway in the House of the Dunedain");
    set_long(BSN("The hallway enters into the Assembly Hall to the north "
      + "and continues to the south. A doorway in the west wall leads into "
      + "a vaulted chamber."));

    add_exit(DUNEDAIN_DIR + "rooms/hall",       "north", 0,  0);
    add_exit(DUNEDAIN_DIR + "rooms/hallw_s2",   "south", check_exit,  0);
    add_exit(DUNEDAIN_DIR + "rooms/dun_shop",   "west",  check_exit,  0);

    floor();
    walls();
    ceiling();

    add_item(({"doorway", "door", "opening", }), BSN(
        "The arched doorway in the west wall is leading into a high vaulted "
      + "chamber. Above the doorway some letters have been chiselled into "
      + "the stone:")
      + "\t\tSAMBE MAHTALION\n");

    add_prop(ROOM_I_INSIDE, 1);
}
