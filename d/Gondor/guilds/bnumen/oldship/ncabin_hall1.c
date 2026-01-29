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

    add_exit(BNUMEN_DIR + "ship/ndeck3", "up", check_exit());
    add_exit(BNUMEN_DIR + "ship/ncabin_hall2", "fore", check_exit());
    add_exit(BNUMEN_DIR + "rooms/train_hall", "starboard", check_exit());
    add_exit(BNUMEN_DIR + "rooms/start_room", "port", check_exit());

}