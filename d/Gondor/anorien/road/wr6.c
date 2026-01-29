/*
 *	/d/Gondor/anorien/road/wr6.c
 *
 *	Coded 1992 by Elessar.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	General revision.
 *
 *  Added exits into Anorien plains. 
 *  Varian 2016
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areadesc("forest");
    set_areatype(8);
    set_area("southwestern");
    set_areaname("Anorien");
    set_land("Gondor");
    set_grass("dark green grass among the trees");
    set_treetype("oak");
    set_mountain("White Mountains");
    set_forest("Druedain Forest");
    set_extraline("The road crossed the Druedain Forest here, " +
        "a gloomy forest with tall trees. The road continues west " +
        "through the forest, while to the southeast it leaves the " +
	    "forest entering the fertile plains of Anorien and following " +
        "the northeastern edge of the forest towards Minas Tirith.");
    add_item(({"mountains","white mountains"}), BSN(
        "To the southwest you can see the snowy peaks of the Ered Nimrais, " +
        "the White Mountains. The mountain range extends far to the west, " +
        "and you can see the two easternmost beacon hills, the Amon Din and " +
        "the Eilenach. "));
    add_item(({"plain","plains"}), 
        "To the north and east vast plains stretch as far as you " +
        "can see.\n");
    add_item(({"thicket", "bushes", "trees", "dense thicket","trees",
            "forest","druedain forest","woods"}),
        "Thick bushes gather beneath ancient trees as the Druedain " +
        "Forest rests up against the edge of the road here. You have " +
        "heard rumours of people living in these woods, but it does " +
        "not seem like you can enter them from here.\n");

    set_no_exit_msg(({"south","southwest"}),
        "The Druedain Forest is too thick to enter from here.\n");

    add_exit(ANO_DIR + "road/wr5", "southeast", 0, 3);
    add_exit(ANO_DIR + "road/wr7", "west",      0, 3);
    add_exit(ANO_DIR + "plains/an8w5n","northwest",0,5,1);
    add_exit(ANO_DIR + "plains/an10w5n","northeast",0,5,1);
    add_exit(ANO_DIR + "plains/an9w5n","north",0,5,1);
    add_exit(ANO_DIR + "plains/an10w6n","east",0,5,1);
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