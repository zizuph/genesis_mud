/*
 *	/d/Gondor/ithilien/nforest/sstream11.c
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
    set_areatype(7);
    set_areadesc("glade close to a stream");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("ash");
    set_extraline("The land is slowly becoming more and more level " +
        "towards the west. The stream is flowing much more slowly " +
        "here than it is further east. The woodlands are thinning " +
        "out, and the glades turn into meadows and fields, interspersed " +
        "with some bushes and thickets. The broad band of the Anduin is " +
        "not far to the west.");
    add_item(({"mountains","mountain-range","mountain","ephel duath"}), 
	BSN("From here the mountains named Ephel Duath appear as dark " +
        "grey shadows beyond the green hills to the east. You judge the " +
        "mountains to be between 5000 to 7000 feet tall, and you guess " +
        "they are many leagues away now."));
    add_item( ({ "forest", "wood", "woods", "herbs", "glades"}), BSN(
        "Giant oaks and hoary ash trees are growing in small groups " +
        "on the glades. Between them lie long lands of green grass " +
        "and herbs. Sages of many kinds are putting forth blue flowers, " +
        "or red, or pale green. The scent of myrtle and lilies hangs " +
        "heavily in the air."));
    add_item( ({"field", "fields", "meadow", "meadows", }), BSN(
        "Between long rows of bushes and small groups of oaks and ash " +
        "trees, there are meadows and fields. But they have long ago " +
        "fallen back to wilderness, since cultivation has been stopped " +
        "at least decades ago."));
    add_item( ({ "flower", "flowers", "primerole", "anemones", "lily",
		 "asphodel", }), BSN(
        "Primeroles and anemones are awake in filbert-brakes; asphodel " +
        "and many lily-flowers are nodding their half-opened heads in " +
        "the grass."));
    add_item( ({ "stream", "pool", "water", }), BSN(
        "The stream that comes down from the slopes in the east is " +
        "flowing slowly towards the Anduin. It is here much broader " +
        "than further to the east, so one cannot cross it anymore " +
        "without swimming."));

    set_drink_from( ({ "stream", "pool", }) );

    set_up_herbs( ({ HERB_DIR + "astaldo", HERB_DIR + "clove",
		     HERB_DIR + "garlic",  HERB_DIR + "sage" }), 
		 ({ "herbs", "flowers", "thickets", "stones", "woods", "groves", }), 3);

    add_exit(ITH_DIR + "nforest/sstream10", "east",      0, 3);
    add_exit(ITH_DIR + "nforest/sstream12", "southwest", 0, 3);

    BEACH;
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
}

public void
init()
{
    ::init();

    init_drink();
}
