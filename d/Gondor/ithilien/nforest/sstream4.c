/*
 *	/d/Gondor/ithilien/nforest/sstream4.c
 *
 *	Coded by Olorin 1993.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

#include <stdproperties.h>

public int     cross_stream();

static object  Rabbit;

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("small stream");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cypress");
    set_extraline("The stream that comes from the small lake continues " +
        "running down the slopes towards the Anduin. It is possible to " +
        "follow the stream walking at its edge. Across the stream, a " +
        "steep bank is rising. Marjorams and new-sprouting parsleys " +
        "and thickets of tamarisk and terebinth grow here along the " +
        "stream, while the cypress woods take over further away from " +
        "the stream. An ever-present sweet and pungent smell of herbs " +
        "and flowers dominates Ithilien, the garden of Gondor.");

    add_exit(ITH_DIR + "nforest/outfall",  "east",      0, 2);
    add_exit(ITH_DIR + "nforest/sstream5", "northwest", 0, 4);

    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    set_up_herbs( ({ HERB_DIR + "tyelka", HERB_DIR + "lothore",
		     HERB_DIR + "sage",   HERB_DIR + "marjoram",
		     HERB_DIR + "thyme",  HERB_DIR + "laurel",
		     HERB_DIR + "clove",  HERB_DIR + "dill", }),
		  ({ "ground", "field", "forest", "bushes", "thickets", 
		     "flowers", }), 3);

    add_item(({"mountains","mountain-range","mountain","ephel duath"}), BSN(
        "From here the mountains named Ephel Duath appear as dark grey " +
        "shadows beyond the stony ridge to the east. You judge the " +
        "mountains to be between 5000 to 7000 feet tall, and you guess " +
        "they are several miles away now."));
    add_item(({"forest","wood","woods","herbs","groves","thickets", 
	       "thicket","grove"}), BSN(
        "Many great trees are growing here, planted long ago, falling " +
        "into untended age amid a riot of careless descendants. There " +
        "are olive and bay, junipers and myrtles, and thymes growing " +
        "in bushes, or with their woody creeping stems mantling in " +
        "deep tapestries the hidden stones, sages of many kinds " +
        "putting forth blue flowers, or red, or pale green; and " +
        "majorams and new-sprouting parsleys, and many other herbs of " +
        "different forms and scents."));
    add_item( ({ "flower", "flowers", "primerole", "anemones", "lily", 
		 "asphodel"}), BSN("Primeroles and anemones are awake " +
	"in filbert-brakes; asphodel and many lily-flowers are nodding " +
        "their half-opened heads in the grass."));
    add_item( ({ "stream", "pool", "water", }), BSN("Here and there " +
        "are little pools in the grass where falling streams are " +
        "halted in cool hollows on their journey down to the Anduin. " +
        "One of the larger streams is the one to the northwest here."));
    add_item( ({ "bank" }), "Across the stream, a steep bank is rising, " +
        "making it impossible to cross the stream here.\n");

    reset_room();
}

public void
reset_room()
{
    ::reset_room();

    if (!objectp(Rabbit))
    {
	Rabbit = clone_npc(Rabbit, NPC_DIR + "rabbit");
	Rabbit->set_restrain_path(ITH_DIR + "nforest/");
    }
}

public int
cross_stream()
{
    write("You cross the small stream.\n");
    return 0;
}

