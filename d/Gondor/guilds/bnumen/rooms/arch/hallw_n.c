/*
 *	/d/Gondor/guilds/bnumen/rooms/hallw_n.c
 *
 *	Coded by Olorin, November 1994
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/guilds/bnumen/rooms/bnumen_room.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/bnumen/lib/bnumen_defs.h"

public void
create_gondor()
{
    set_short("Northern Hallway in the House of the Black Numenoreans");
    set_long(BSN("This is a paved passage, long and empty. It connects "
      + "the great Assembly Hall to the south to a smaller chamber "
      + "north of here. A large stone arch is leading into a hall "
      + "to the west."));

    add_item(({"arch", "archway", "large arch", "large arch", "west arch",
        "western arch", "hall", }), BSN(
        "Through the large archway which opens in the western wall a large "
      + "hall can be seen. The hall is full of many shelves filled with books "
      + "and scrolls. Above the arch letters have been chiselled into the "
      + "stone:")
      + "\t\tMARDE PARMALION\n");

    add_exit(BNUMEN_DIR + "rooms/join_room", "north", "@@check_exit",  0);
    add_exit(BNUMEN_DIR + "rooms/hall", "south", 0,  0);
    add_exit(BNUMEN_DIR + "rooms/lib_public", "west", 0,  0);

    ceiling();
    walls();
    floor();
}

int
check_exit()
{
    if (TP->query_race() == BNUMEN_RACE || TP->query_wiz_level())
        return 0;

    write("Only humans may proceed here!\n");
    return 1;
}
