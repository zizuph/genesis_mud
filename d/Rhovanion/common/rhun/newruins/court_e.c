/* Author: Modred 950816 */


inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h";

create_room()
{
    set_short("East end of the courtyard");
    set_long("You stand in the east end of an almost circular"+
    " courtyard. The remains of a building lies strewn around"+
    " the courtyard. Not that much remain, only the foundation"+
    " and a few parts of the roof. To the west, you can see what"+
    " looks like an iron pole, and to the nortwest and southwest"+
    " the courtyard spreads out.\n");

    add_exit(RHUN_DIR + "newruins/court_n","northwest");
    add_exit(RHUN_DIR + "newruins/court_s","southwest");
    add_exit(RHUN_DIR + "newruins/court_c","west");

    add_item(({"remains", "building"}),"The building"+
    " has completely collapsed during the centuries, but judging"+
    " by the look of the foundation it must have been some kind of"+
    " storeroom\n");

    add_item(({"foundation"}), "The foundation is made out of "+
    "the same kind of stone as in the walls, roughly hewn to form"+
    " blocks.\n");

}
