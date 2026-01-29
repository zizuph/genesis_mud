/*
 *	/d/Gondor/anorien/nimrais/rimvalley2.c
 *
 *	Coded by Elessar, 1992
 *
 *	Modification log:
 *	 7-Feb-1997, Olorin:	Changed inheritance.
 *      16-Mar-2000, Stern :    added OBJ_I_CONTAIN_WATER property.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
reset_room()
{
    ::reset_room();

    if (!present("torch", TO))
        clone_object(OBJ_DIR + "torch")->move(TO);
}

public void
create_area_room()
{
    string *herbs;

    set_areatype(2);
    set_areadesc("field in a valley");
    set_grass("thick");
    set_area("central");
    set_areaname("the White Mountains");
    set_land("Gondor");
    set_extraline("The valley leads south deeper into the "+
    "White Mountains. The slopes in the valleysides are not really steep "+
    "here, compared to the looks of the hillsides to the south. A small "+
    "stream runs out of the valley here.");
    add_item("stream", "The stream is quite small and cold, " +
	"originating from the snowy peaks in the White Mountains to the south.\n");
    set_drink_from("stream");

    add_exit(ANO_DIR + "nimrais/rimvalley1",   "north", 0, 2);
    add_exit(ANO_DIR + "nimrais/trolls/path1", "south", 0, 2);

    herbs = HERB_MASTER->query_herbs( ({ "hills", "moderate", }));
    set_up_herbs( ({ ONE_OF_LIST(herbs), ONE_OF_LIST(herbs), 
		     ONE_OF_LIST(herbs),}),
		  ({ "ground",  }), 3);

    add_prop(OBJ_I_CONTAIN_WATER, -1);  
 
    reset_room();
}

public void
init()
{
    ::init();
    init_drink();
}
