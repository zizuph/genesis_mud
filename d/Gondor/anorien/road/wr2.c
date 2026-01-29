/*
 *	/d/Gondor/anorien/road/wr2.c
 *
 *	Coded 1992 by Elessar.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	General revision.
 *  Added exits into Anorien plains. 
 *  Varian 2016
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areadesc("green, grassy field");
    set_areatype(8);
    set_area("southern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_grass("dry, light green grass");
    set_extraline("The road continues south towards Minas Tirith, the White " +
        "Tower of Guard, and northwest it leads to Rohan, the Kingdom of " +
        "the Horse-riders. Far to the east you hear the sound of the mighty " +
        "river Anduin, and far to the southwest you see the White Mountains. " +
        "The plains of Anorien stretch out north and east.");
    add_item(({"river","anduin"}), BSN(
        "It is not possible to see the Anduin from here, " +
        "but from the east you can hear the sound of the might river " +
        "running southwards to its mouths at the Bay of Belfalas. "));
    add_item(({"mountains","white mountains"}), BSN(
        "To the southwest you can see the snowy peaks of the Ered Nimrais, " +
        "the White Mountains. The mountain range extends far to the west, " +
        "and you can see the two easternmost beacon hills, the Amon Din and " +
        "the Eilenach. "));
    add_item(({"thicket", "bushes", "trees", "dense thicket"}),
        "Large clusters of bushes gather all along the west side of " +
        "the road, but they are far too thick for you to enter.\n");
    set_no_exit_msg(({"southwest","west"}),
        "The bushes are too thick to enter from here.\n");

    add_exit(ANO_DIR + "road/wr1", "south",     0, 3);
    add_exit(ANO_DIR + "road/wr3", "northwest", 0, 3);
    add_exit(ANO_DIR + "plains/an14w11n","southeast",0,5,1);
    add_exit(ANO_DIR + "plains/an14w10n","east",0,5,1);
    add_exit(ANO_DIR + "plains/an14w9n","northeast",0,5,1);
    add_exit(ANO_DIR + "plains/an13w9n","north",0,5,1);
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
