#pragma strict_types

#include "defs.h"

inherit MOUNTBASE;

public int
leave_msg()
{
    if (TP->test_bit("Calia",
        ELDORAL_QUEST_GROUP, ELDORAL_SECRET_WAY_BIT))
        return 0;

    write("Having discovered this place, you feel certain that in " +
        "the future you'll be able to return this way.\n");
    TP->set_bit(ELDORAL_QUEST_GROUP, ELDORAL_SECRET_WAY_BIT);
    return 0;
}

public void
create_room()
{
    extra = "You seem to be surrounded on all sides by close-pressing " +
        "trees, the only break in the foliage is a narrow ledge " +
        "of rock that juts up from through the soft ground of " +
        "the forest floor. ";

    create_trail();
    add_item(({"ledge", "rock", "ledge of rock", "narrow ledge"}),
        "The ledge appears to be the roof of some sort of " +
        "cave that descends beneath the forest floor here.\n");

    add_exit(CAVERNS + "pas13", "cave");
    add_exit(MOUNT + "m10", "west", "@@leave_msg");
}
