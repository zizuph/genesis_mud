/*
 * Tunnel6.c
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
    add_exit(LAIR_DIR + "tunnel5", "west",  0, 4);
    add_exit(LAIR_DIR + "lair1",   "north", "@@block_exit@@", 4);
    add_exit(LAIR_DIR + "tunnel7", "east",  0, 4);

    make_the_room();
}

int block_exit()
{
    if (TP->query_wiz_level())
    {
        write("This part is still closed for mortals!\n");
        return 0;
    }
    write("A large cobweb blocks your progress in that direction!\n");
    return 1;
}
