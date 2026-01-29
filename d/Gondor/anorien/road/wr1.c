/*
 *  /d/Gondor/anorien/road/wr1.c
 *
 *  Coded 1992 by Elessar.
 *
 *  Modification log:
 *  30-Jan-1997, Olorin:    General revision.
 *  Added exits into Anorien plains. 
 *  Varian 2016
 */
#pragma strict_types
inherit "/d/Gondor/common/lib/area_room.c";
#include "/d/Gondor/defs.h"
public void
create_area_room()
{
    set_areadesc("green field");
    set_areatype(8);
    set_area("southern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_grass("dry, light green grass");
    set_extraline("To the south you can make out the great wall, Rammas " +
        "Echor, surrounding the Fields of Pelennor outside Minas Tirith. " +
        "The road also continues north through the plains of Anorien, " +
        "while another road branches off southeast, going towards the " +
        "ruins of Osgiliath upon Anduin. All along the west side of the " +
        "road, a dense thicket rests below the towering peaks of the White " +
        "Mountains.");
    set_no_exit_msg(({"southwest","west","northwest"}),
        "The bushes are too thick to enter from here.\n");
    add_item(({"mountains", "white mountains", "ered nimrais"}),
        "Off in the distance to the west, the rugged peaks " +
        "of the White Mountains claw at the empty sky above.\n");
    add_item(({"thicket", "bushes", "trees", "dense thicket"}),
        "Large clusters of bushes gather all along the west side of " +
        "the road, but they are far too thick for you to enter.\n");
    add_exit(ANO_DIR + "road/wr2", "north",     0, 3);
    add_exit(ANO_DIR + "road/or1", "southeast", 0, 3);
    add_exit(PEL_DIR + "noutgate", "south",     0, 3);
    add_exit(ANO_DIR + "plains/an14w10n","northeast",0,3,1);
    add_exit(ANO_DIR + "plains/an14w11n","east",0,3,1);
}
string
query_dir_to_gate()
{
    return "south";
}
/*
 This was used while the plains were under construction. Now open
 Varian - August 2016
int
block()
{
    if (this_player()->query_wiz_level()) return 0;
    write("You should be able to enter the plains of Anorien soon!\n");
    return 1;
}
*/
