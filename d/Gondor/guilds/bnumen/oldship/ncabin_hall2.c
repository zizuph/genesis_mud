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
    add_exit(BNUMEN_DIR + "ship/ncabin_hall3", "fore", check_exit());
    add_exit(BNUMEN_DIR + "ship/ncabin_hall1", "aft", check_exit());

    walls(4);
    ceiling(4);
    floor(4);


}
