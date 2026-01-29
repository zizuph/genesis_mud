/*
 *	/d/Gondor/ithilien/nforest/sstream7.c
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
    set_areadesc("stream");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cedar");
    set_extraline("To the north, the land rises a bit to a broad " +
        "ledge overgrown with trees and bushes. To the west the way is " +
        "blocked by a sheer cliff face that is interrupted only by a " +
        "narrow channel through which the swift stream disappears. " +
        "Cypress and cedar trees grow here in thickets, and bushes " +
        "cling to the mossy crags of the hillside.");

    add_item(({"mountains","mountain-range","mountain","ephel duath"}),BS(
    "The view towards the mountains in the east is blocked by the tree tops.\n"));
    add_item(({"ledge","bushes"}), BSN(
    "The ledge to the north is overgrown with trees and bushes, which " +
    "make passage in that direction impossible. "));
    add_item(({"forest","wood","woods","herbs","groves","thickets","thicket",
	       "grove"}), BSN(
        "Many great trees are growing here, planted long ago, falling into " +
        "untended age amid a riot of careless descendants. There are olive " +
        "and cedars, junipers and myrtles, and majorams and new-sprouting " +
        "parsleys, and many other herbs of different forms and scents."));
    add_item(({"flower","flowers","primerole","anemones","lily","asphodel"}), 
	BSN("Primeroles and anemones are awake in filbert-brakes; asphodel " +
        "and many lily-flowers are nodding their half-opened heads in the " +
        "grass."));
    add_item(({"stream","pool","water"}), BSN("With the relentless " +
        "force of water the swift stream has forced its way through " +
        "the rock wall to the west here. Curling and rushing and " +
        "flecked with foam, it enters a smooth-hewn channel and " +
        "disappears between the rocks. There is no way you can follow " +
        "the stream any further."));
    add_item(({"channel","rock","rocks"}), BSN("The only opening " +
        "in the rock wall is a small smooth-hewn channel through which " +
        "the stream disappears. There is no way you can follow the " +
        "stream any further. The sheer cliff face is steep and " +
        "featureless except for the channel. It rises for many " +
        "feet, so that there is no way to scale it."));

    add_exit(ITH_DIR + "nforest/sstream8", "northwest", 0, 4);
    add_exit(ITH_DIR + "nforest/sstream6", "southeast", 0, 4);

    set_up_herbs( ({ HERB_DIR+"clove", HERB_DIR+"marjoram",
		     HERB_DIR+"basil", HERB_DIR+"tuo", 
		     SHIRE_HERB_DIR+"parsley", }), 
		  ({ "herbs", "flowers", "thickets", "stones", 
		     "woods", "groves"}), 3);

    BEACH;
    add_prop(OBJ_I_CONTAIN_WATER, -1);
    set_drink_from( ({ "stream", "pool", }) );
}

public void
init()
{
    ::init();

    init_drink();
}