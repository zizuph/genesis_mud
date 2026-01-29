/*
 * Hole1.c
 *
 * The entrance of Shelobs lair, Torech Ungol.
 *
 * /Mercade, 18 july 1993
 */

inherit "/d/Gondor/mordor/ungol/lair/std_lair";
#include "/d/Gondor/defs.h"

void
create_room()
{
    add_exit(LAIR_DIR + "stunnel4",  "west",  0, 4);
    add_exit(UNGOL_DIR + "path2", "south", "@@no_exit", 4);

    make_the_room(" From the south you feel a little breeze and suspect " +
        "that you will find an exit from this horrible lair in that " +
        "direction.");
}

int
no_exit()
{
    if (TP->query_wiz_level())
    {
        write("This part is still closed for mortals!\n");
        return 0;
    }
    write("You cannot escape from Shelob's lair yet.\n");
    return 1;
}
