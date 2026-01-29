#pragma save_binary

inherit "/d/Gondor/guilds/bnumen/rooms/bnumen_room.c";

#include "/d/Gondor/common/lib/time.h"

#include "/d/Gondor/defs.h"


void
create_cabin()
{
    set_short("A hallway below decks");
    set_long(long_cabin_level_1(4) + 
        "Two doors, one to port and " +
        "one to starboard, lead into adjoining chambers.\n");
    walls(4);
    ceiling(4);
    floor(4);

    add_exit(BNUMEN_DIR + "ship/ncabin_hall4", "fore", check_exit());
    add_exit(BNUMEN_DIR + "ship/ncabin_hall2", "aft", check_exit());

    add_exit(BNUMEN_DIR + "rooms/board_room", "starboard", check_exit());
    add_exit(BNUMEN_DIR + "rooms/post", "port", check_exit());

}