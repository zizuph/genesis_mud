#pragma save_binary

inherit "/d/Gondor/guilds/bnumen/rooms/bnumen_room.c";

#include "/d/Gondor/common/lib/time.h"

#include "/d/Gondor/defs.h"


void
create_cabin()
{
    set_short("A hallway below decks");
    set_long(long_cabin_level_1(4) + 
        "A ladder leads up to the deck. Two doors, one to port and " +
        "one to starboard, lead into adjoining chambers.\n");
    walls(4);
    ceiling(4);
    floor(4);

    add_exit(BNUMEN_DIR + "ship/ndeck1", "up", check_exit());
    add_exit(BNUMEN_DIR + "ship/ncabin_hall3", "aft", check_exit());


    add_exit(BNUMEN_DIR + "rooms/lib_lords", "fore", check_exit());
    add_exit(BNUMEN_DIR + "rooms/lib_public", "port", check_exit());
    add_exit(BNUMEN_DIR + "rooms/lib_houses", "starboard", check_exit());

}