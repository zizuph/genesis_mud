#pragma strict_types
inherit "/d/Gondor/common/lib/area_room.c";

#include <ss_types.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("deep brown bed of fern");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cedar");
    set_extraline("You are standing in a deep brown bed of last "
      + "year's fern. Further up south is a thicket of dark-leaved "
      + "bay-trees climbing up a steep ridge that is crowned with "
      + "cedars. Down to the north is a shallow dell, in which a "
      + "small clear lake rests. You can see a small stream coming "
      + "down from the northeastern hillslopes, entering the lake "
      + "in one end, and continuing out below at the other end.");
    add_item(({"mountains","mountain-range","mountain","ephel duath"}),
        BSN("From here the mountains named Ephel Duath appear as "
      + "dark grey shadows beyond the stony ridge to the east. "
      + "You judge the mountains to be between 5000 to 7000 feet "
      + "tall, and you guess they are several miles away now."));
    add_item(({"forest","wood","woods","herbs","groves","thickets",
       "thicket","grove"}), BSN(
       "Many great trees are growing here, planted long ago, "
     + "falling into untended age amid a riot of careless "
     + "descendants. There are olive and bay, junipers and "
     + "myrtles, and thymes growing in bushes, or with their "
     + "woody creeping stems mantling in deep tapestries the "
     + "hidden stones, sages of many kinds putting forth blue "
     + "flowers, or red, or pale green; and majorams and "
     + "new-sprouting parsleys, and many other herbs of different "
     + "forms and scents."));
    add_item(({"stone","stones","rock","rocks"}),BSN(
       "To the east, where the slope rises to the ridge, in "
     + "several places the soil retreats to make room for areas of "
     + "uncovered rock. Here saxifrages and stonecrops are "
     + "growing. To the northeast, from on of these stony areas, a "
     + "rock wall rises up to the ridge."));
    add_item(({"flower","flowers","primerole","anemones","lily",
       "asphodel"}), BSN(
       "Primeroles and anemones are awake in filbert-brakes; "
     + "asphodel and many lily-flowers are nodding their "
     + "half-opened heads in the grass."));
    add_item( ({ "bed", "fern", "ferns", }), BSN(
        "The ground is covered by a thick bed of brown ferns "
      + "here. The ferns are of last year's growth."));
    add_item(({"stream","pool","water"}),BSN(
       "Here and there are little pools in the grass where falling "
     + "streams are halted in cool hollows on their journey down "
     + "to the Anduin. One of the larger streams can be seen to the "
     + "north, where it enters the lake."));
    add_item(({"lake", "basin", "pool", "water"}), BSN(
       "The small lake lies in the broken ruins of an ancient stone "
     + "basin. A small stream running down from the east is feeding "
     + "it. Water-lily leaves are floating on the dark "
     + "gently-rippling surface of the water; the stream spills ever "
     + "softly out over a stony lip at the far end."));

    add_exit(ITH_DIR + "nforest/bank3", "north", 0, 1);
    add_exit(ITH_DIR + "nforest/bank2", "west",  0, 1);

    set_up_herbs( ({ HERB_DIR + "laurel", HERB_DIR + "myrtle",
		     HERB_DIR + "thyme", HERB_DIR + "sage",
		     HERB_DIR + "marjoram",
		     SHIRE_HERB_DIR + "parsley", }),
		  ({ "forest", "flowers", "wood", "thicket", }), 3);
}
