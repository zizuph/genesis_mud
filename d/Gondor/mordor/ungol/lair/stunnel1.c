/*
 * Stunnel1.c
 *
 * The entrance of Shelobs lair, Torech Ungol.
 *
 * /Mercade, 18 july 1993
 *
 * add_item( ({"cobwebs", "cobweb"})  - Znagsnuf
 */

inherit "/d/Gondor/mordor/ungol/lair/std_lair";
#include "/d/Gondor/defs.h"

void
create_room()
{
    add_exit(LAIR_DIR + "lair1",    "west",      "@@block_exit@@", 4);
    add_exit(LAIR_DIR + "deadend6", "northwest", 0, 4);
    add_exit(LAIR_DIR + "stunnel2", "southeast", 0, 4);

    add_item( ({"cobwebs", "cobweb"}), "A cobweb large enough to cover "
              + "the whole exit.\n");

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