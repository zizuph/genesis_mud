/*
 * Tunnel10.c
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
    add_exit(LAIR_DIR + "tunnel9", "west", 0, 4);
    add_exit(LAIR_DIR + "path1",   "east", "@@no_exit", 4);

    make_the_room(" You feel a cool breeze comming from the east and you " +
        "suspect to find an exit from this horrible lair in that direction.");
}

int
no_exit()
{
    if (TP->query_wiz_level())
    {
        write("This part is still closed for mortals!\n");
        return 0;
    }
    WRITE("You feel a soft wall prevent your exit from Torech Ungol!");
    return 1;
}
