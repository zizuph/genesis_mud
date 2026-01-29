/* An overgrown path to the old guild-hall by Mucalytic May the 20th '96. */

#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLACE_ROOM

void create_solace_room()
{
    set_short("An overgrown path");
    set_long("You seem to be on an overgrown path below a canopy of tall "+
        "evergreen trees. The path winds along in a northwest-southeast "+
        "direction through a tangle of bushes and roots and branches. "+
        "Further along to the southeast, you can just see a clearing. The "+
        "only other option is further northwest through the overgrowth.\n");

    add_exit(HROAD + "path1", "northwest", 0, 2);
    add_exit(HROAD + "clearing", "southeast", 0, 2);

    add_item("canopy", "A ceiling of branches and leaves above your head.\n");

    add_item(({"roots", "branches", "ovregrowth"}), "You notice nothing of "+
        "interest.\n");

    add_item("bushes", "They are a lovely green colour and rustle in the "+
        "wind. You see nothing more of interest.\n");

    add_item(({"path", "overgrown path"}), "An almost invisible pathway "+
        "through the vegetation leading southeast to northwest.\n");

    add_item(({"trees", "tall trees", "evergreen trees", "tall evergreen "+
        "trees"}), "Very tall trees with long thin trunks and branches many "+
        "metres up up the air.\n");

    add_item("clearing", "You can barely see it, due to the tangle of over"+
        "growth hereabouts. You decide that to see it better, it would be "+
        "best to walksoutheast towards it.\n");
}
