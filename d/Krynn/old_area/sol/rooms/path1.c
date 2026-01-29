/* An overgrown path to the old guild-hall by Mucalytic May the 20th '96. */

#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLACE_ROOM

void create_solace_room()
{
    set_short("An overgrown path");
    set_long("You find yourself on an overgrown path amidst a canopy of "+
        "tall evergreen trees. Green bracken and slippery moss cover the "+
        "ground and the sound of small birds in the trees reaches your "+
        "ears. The only exit from here seems to be further to the southeast "+
        "along the path, although you think you might be able to squeeze "+
        "yourself through the bushes to the northwest.\n");

    add_exit(HROAD + "path2", "southeast", 0, 2);
    add_invis_exit(HROAD + "road1", "northwest", 0, 2);

    add_item("ground", "You see nothing special about it.\n");

    add_item("canopy", "A ceiling of branches and leaves above your head.\n");

    add_item(({"moss", "slippery moss"}), "Wet green moss on the trees and "+
        "boulders around this area.\n");

    add_item(({"path", "overgrown path"}), "An almost invisible pathway "+
        "through the vegetation leading southeast to northwest.\n");

    add_item("bushes", "There is nothing special about them except for the "+
        "fact that that you can just see a road further on beyond them.\n");

    add_item(({"trees", "tall trees", "evergreen trees", "tall evergreen "+
        "trees"}), "Very tall trees with long thin trunks and branches many "+
        "metres up up the air.\n");
}
