/*
 *	/d/Gondor/ithilien/nforest/sstream2.c
 *
 *	Coded by Olorin 1993.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 *   04-Okt-2008, Eowul:    Added drinking support 
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include "/d/Gondor/defs.h"

#include <stdproperties.h>

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("small stream");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cypress");
    set_extraline("The falling stream continues down westwards, but halts "+
    "in cool hollows in little pools here and there, on its journey "+
    "down to Anduin. Asphodel and lily-flowers nod their half-opened heads "+
    "in the deep green grass by the stream, and junipers and myrtles "+
    "growing in thickets among the tall green cypress trees. Further down, the " +
    "small streams seems to enter a shallow dell.");
    add_item(({"mountains","mountain-range","mountain","ephel duath"}),BS(
    "From here the mountains named Ephel Duath appear as dark grey shadows " +
    "beyond the stony ridge to the east. "+
    "You judge the mountains to be between 5000 to 7000 feet tall, "+
    "and you guess they are several kilometers away now.\n"));
    add_item(({"forest","wood","woods","herbs","groves","thickets","thicket","grove"}),BS(
    "Many great trees are growing here, planted long ago, falling into untended age amid a riot " +
    "of careless descendants. There are olive and bay, junipers and myrtles, " +
    "and thymes growing in bushes, or with their " +
    "woody creeping stems mantling in deep tapestries the hidden stones, sages of many kinds putting forth blue " +
    "flowers, or red, or pale green; and marjorams and new-sprouting " +
    "parsleys, and many other herbs of different forms and scents. \n"));
    add_item(({"flower","flowers","primerole","anemones","lily","asphodel"}),BS(
    "Primeroles and anemones are awake in filbert-brakes; asphodel and many lily-flowers are nodding their " +
    "half-opened heads in the grass. \n"));
    add_item(({"stream","pool","water"}),BS(
    "Here and there are little pools in the grass where falling streams are halted in cool hollows on their " +
    "journey down to the Anduin. One of the larger streams can be seen through the trees to the west. \n"));
    add_item(({"clearing","dell"}), BSN(
    "Through the trees to the west, you can make out a clearing "+
    "in what looks like a small dell. The stream runs down into it."));

    add_exit(ITH_DIR + "nforest/sstream1", "northeast", 0, 1);
    add_exit(ITH_DIR + "nforest/sstream3", "west",      0, 1);

    set_drink_from( ({ "stream", "pool", }) );
    add_prop(OBJ_I_CONTAIN_WATER, -1);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    set_up_herbs( ({ HERB_DIR+"fennel", HERB_DIR+"rosemary",
		     HERB_DIR+"thyme",  HERB_DIR+"sage", 
		     HERB_DIR+"laurel", HERB_DIR+"marjoram", 
		     SHIRE_HERB_DIR+"parsley", HERB_DIR+"redweed", }),
 		  ({"forest","ground","field","flowers","forest"}), 3);
}

public void
init()
{
    ::init();

    init_drink();
}