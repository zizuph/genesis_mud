/*
 *	/d/Gondor/ithilien/nforest/sstream1.c
 *
 *	Coded by Olorin 1993.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("small stream");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cypress");
    set_extraline("The small stream quickly runs down from the stony " +
	"ridge covered with fir and cedar trees to the east. It continues " +
        "downhill on its journey to the Anduin. Under the trees there " +
        "are groves and thickets of tamarisk and terebinth, and thymes " +
        "are growing in bushes. Everywhere, sweet odours are arising from " +
        "the herbs and flowers.");
    add_item(({"mountains","mountain-range","mountain","ephel duath"}), BSN(
	"From here the mountains named Ephel Duath appear as dark grey " +
        "shadows beyond the stony ridge to the east. You judge the " +
        "mountains to be between 5000 to 7000 feet tall, and you guess that " +
        "they are several miles away now."));
    add_item(({"forest","wood","woods","herbs","groves","thickets",
	       "thicket","grove"}), BSN(
	"Many great trees are growing here, planted long ago, falling into " +
        "untended age amid a riot of careless descendants. There are olive " +
        "and bay, junipers and myrtles, and thymes growing in bushes, or " +
        "with their woody creeping stems mantling in deep tapestries the " +
        "hidden stones, sages of many kinds putting forth blue flowers, or " +
        "red, or pale green; and marjorams and new-sprouting parsleys, and " +
        "many other herbs of different forms and scents."));
    add_item(({"stone","stones","rock","rocks"}), BSN(
        "To the east, where the slope rises to the ridge, in several places " +
        "the soil retreats to make room for areas of uncovered rock. Here " +
        "saxifrages and stonecrops are growing. To the northeast, from on of " +
        "these stony areas, a rock wall rises up to the ridge."));
    add_item(({"flower","flowers","primerole","anemones","lily","asphodel"}), BSN(
        "Primeroles and anemones are awake in filbert-brakes; asphodel and " +
        "many lily-flowers are nodding their half-opened heads in the grass."));
    add_item(({"stream","pool","water"}), BSN(
        "Here and there are little pools in the grass where falling streams " +
        "are halted in cool hollows on their journey down to the Anduin. One " +
        "of the larger streams can be seen through the trees to the south."));

    add_exit(ITH_DIR + "nforest/downhill", "east",      0, 1);
    add_exit(ITH_DIR + "nforest/sstream2", "southwest", 0, 1);

    set_up_herbs( ({ HERB_DIR + "saffron", HERB_DIR + "mint",
		     HERB_DIR + "thyme",   HERB_DIR + "sage",
		     HERB_DIR + "laurel",  HERB_DIR + "marjoram",
		     HERB_DIR + "lothore", HERB_DIR + "hemlock", 
		     SHIRE_HERB_DIR + "parsley", }),
		  ({"forest","ground","field","flowers","forest"}), 3);
}
