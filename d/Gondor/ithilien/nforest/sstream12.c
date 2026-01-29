/*
 *	/d/Gondor/ithilien/nforest/sstream12.c
 *
 *	Coded by Olorin, 1993.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(3);
    set_areadesc("field");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("ash");
    set_grass("long green");
    set_extraline("Long ago these fields must have been cultivated, " +
        "but they seem to have fallen back to the wilderness decades " +
        "ago. A stream is flowing through the field to the Anduin in " +
        "the west. Some groups of ash trees are standing in the fields, " +
        "and a few willows are bordering the stream on both banks. To " +
        "the west, a road is running from south to north along the " +
        "banks of the Anduin.");
    add_item( ({ "mountains", "mountain-range", "mountain", "ephel duath", }),
	BSN("From here the mountains named Ephel Duath appear as dark grey " +
        "shadows beyond the green hills to the east. You judge the mountains " +
        "to be between 5000 to 7000 feet tall, and you guess they are many " +
        "leagues away now."));
    add_item( ({ "forest", "wood", "woods", "herbs", "field", "fields", }),
        BSN("Hoary ash trees are growing in small groups on the field. " +
        "Between them lie long lands of green grass and herbs. The " +
        "scent of parsleys, mints, and irises hangs heavily in the air."));
    add_item( ({ "flower"," flowers", "primerole", "anemones", "lily",
		 "asphodel", }), BSN(
        "Primeroles and anemones are awake in filbert-brakes; asphodel " +
        "and many lily-flowers are nodding their half-opened heads in " +
        "the grass."));
    add_item( ({ "stream", "pool", "water", }), BSN("The stream that " +
        "comes down from the slopes in the east is flowing slowly " +
        "towards the Anduin, which it joins not far west of here. It " +
        "is too broad to cross here easily."));
    add_item( ({ "willow", "willows", }), BSN(
        "On both banks of the stream you can see a few willows " +
        "growing. Their long thin branches are hanging down over " +
        "the water."));

    set_up_herbs( ({ HERB_DIR + "caraway", HERB_DIR + "garlic", 
		     HERB_DIR + "lothore", HERB_DIR + "mint", 
		     HERB_DIR + "redweed", HERB_DIR + "saffron", }),
		  ({ "herbs", "flowers", "thickets", "stones", "woods", 
		     "groves", }), 4);
    add_exit(ITH_DIR + "nforest/sstream11", "northeast", 0, 3);
    add_exit(ITH_DIR + "road/rr9",          "west",      0, 3);

    set_drink_from( ({ "stream", "pool", }) );
    BEACH;
    add_prop(OBJ_I_CONTAIN_WATER,1);
}

public void
init()
{
    ::init();

    init_drink();
}
