/*
 *	/d/Gondor/common/dunedain/rooms/hallw_n.c
 *
 *	Coded by Olorin, November 1994
 *
 * ChangeLog:
 * Palmer - May 14 2006:
 * Removed north exit block if wizard.
 *
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/dunedain/rooms/dun_room.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/dunedain/lib/dunedain_defs.h"

public void
create_gondor()
{
    set_short("Northern Hallway in the House of the Dunedain");
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

    add_exit(DUNEDAIN_DIR + "join_room", "north", "@@check_exit",  0);
    add_exit(DUNEDAIN_DIR + "rooms/hall", "south", 0,  0);
    add_exit(DUNEDAIN_DIR + "rooms/lib_public", "west", 0,  0);

    ceiling();
    walls();
    floor();
}

int
check_exit()
{
    if (TP->query_race() == DUNEDAIN_RACE || TP->query_wiz_level())
        return 0;

    write("Only humans may proceed here!\n");
    return 1;
}
