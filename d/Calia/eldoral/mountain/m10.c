#pragma strict_types

#include "defs.h"

inherit MOUNTBASE;

public int
see_secret()
{
    if (!TP->test_bit("Calia",
        ELDORAL_QUEST_GROUP, ELDORAL_SECRET_WAY_BIT))
    {
        write("There is no obvious exit east.\n");
        return 1;
    }
    else
    {
        write("Remembering the secret passage to the island, you " +
            "push through the trees, knowing there's a place " +
            "beyond them.\n");
        return 0;
    }
}

public void
create_room()
{
    create_trail();
    add_exit(MOUNT + "m11", "northwest");
    add_exit(MOUNT + "m7", "southwest");
    add_exit(MOUNT + "secret", "east", "@@see_secret", 1, 1);
}
