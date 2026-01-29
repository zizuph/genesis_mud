/*
 *      /d/Gondor/ithilien/nforest/downhill.c
 *
 *      Coded 1993 by Olorin.
 *
 *      Modification log:
 *      31-Jan-1997, Olorin: Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("gentle slope");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("olive and bay");
    set_extraline("To the east, there is a stony ridge covered with " +
        "fir and cedar trees. Under the trees there are groves and " +
        "thickets of tamarisk and terebinth. Here thymes are growing in " +
        "bushes, and where rocks are visible, they are starred with " +
        "saxifrages and stonecrops. To the northeast, a rocky wall " +
        "rises up to the ridge. Everywhere, sweet odours are arising " +
        "from the herbs and flowers. The slope is running down to " +
        "west, where you can see a little stream running through the " +
        "forest.");
    add_item(({"mountains","mountain-range","mountain","ephel duath"}), 
        BSN("From here the mountains named Ephel Duath appear as " +
        "dark grey shadows beyond the stony ridge to the east. You " +
        "judge the mountains to be between 5000 to 7000 feet tall, " +
        "and you guess they are several kilometers away now."));
    add_item( ({ "forest", "wood", "woods","herbs","groves","thickets",
		 "thicket", "grove", }), BSN(
        "Many great trees are growing here, planted long ago, falling " +
        "into untended age amid a riot of careless descendants. There " +
        "are olive and bay, junipers and myrtles, and thymes growing " +
        "in bushes, or with their woody creeping stems mantling in " +
        "deep tapestries the hidden stones, sages of many kinds putting " +
        "forth blue flowers, or red, or pale green; and majorams and " +
        "new-sprouting parsleys, and many other herbs of different " +
        "forms and scents."));
    add_item(({"wall","slope","ridge","stone","stones","rock","rocks"}),
	BSN("To the east, where the slope rises to the ridge, in several " +
        "places the soil retreats to make room for areas of uncovered " +
        "rock. Here saxifrages and stonecrops are growing. To the " +
        "northeast, from one of these stony areas, a rock wall rises " +
        "up to the ridge."));
    add_item( ({ "flower", "flowers", "primerole", "anemones", "lily", 
		 "asphodel", }),BSN(
        "Primeroles and anemones are awake in filbert-brakes; asphodel " +
        "and many lily-flowers are nodding their half-opened heads in " +
        "the grass."));
    add_item( ({ "stream", "pool", "water", }), BSN(
        "Here and there are little pools in the grass where falling " +
        "streams are halted in cool hollows on their journey down to " +
        "the Anduin. One of the larger streams can be seen through the " +
        "trees to the west."));

    set_up_herbs( ({ HERB_DIR + "clove",  HERB_DIR + "curugwath", 
		     HERB_DIR + "laurel", HERB_DIR + "marjoram", 
		     HERB_DIR + "sage",   HERB_DIR + "tuo", }),
		 ({ "forest", "ground", "field", "flowers", }), 3);

    add_exit(ITH_DIR + "nforest/ridge",    "northeast", 0, 3);
    add_exit(ITH_DIR + "nforest/sstream1", "west",      0, 2);
}
