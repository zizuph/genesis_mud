/* A clearing at the entrance to the guild by Mucalytic May the 20th '96. */

#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLACE_ROOM

void create_solace_room()
{
    set_short("A clearing in the overgrowth");
    set_long("You find yourself in a small clearing in the tangle of "+
        "overgrowth hereabouts. In the centre of it, you see a grand "+
        "but decrepit-looking entrance to some building lost in the "+
        "tangle of bushes and roots and branches that entirely cover the "+
        "extent of this area. The only other exit leads along a path "+
        "to the northwest.\n");

    add_exit(OLD_GUILD, "south", 0, 1);
    add_exit(HROAD + "path2", "northwest", 0, 2);

    add_item(({"roots", "branches", "overgrowth"}), "You notice nothing of "+
        "interest.\n");

    add_item(({"clearing", "small clearing"}), "You seem to be standing in "+
        "the middle of it.\n");

    add_item(({"path", "overgrown path"}), "An almost invisible pathway "+
        "through the vegetation leading northwest.\n");

    add_item("bushes", "They are a lovely green colour and rustle in the "+
        "wind. You see nothing more of interest.\n");

    add_item(({"building", "entrance", "decrepit-looking entrance"}), "The "+
        "building looks proud and grand as it thrusts itself from the wild "+
        "growth trying to encompass it. It still seems a mystery, so you "+
        "decide that the best option would be to simply walk south into it.\n");
}
