/*
 *   /d/Gondor/ithilien/poros/p1.c
 *
 *   This is the first part of a path that leads from the Harad Road, 
 *   through Southern Ithilien to a hidden Corsair base along the 
 *   Poros. The path begins just north of the Fords of the Poros, and
 *   essentially parallels the river to the base.
 *
 *   Talisan, December 1995
 *   Serif: typo fix November 2001
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/herb_list.h"
#include "/d/Gondor/ithilien/poros/poros_herbs.h"

void
create_area_room()
{
      set_land("Gondor");
      set_areaname("Ithilien");
      set_area("southern");
      set_areadesc("path");
      set_areatype(1);

      set_extraline("The narrow path follows along the northern shore of the "
          + "river Poros. Both river banks are lined with tall trees and lush "
          + "bushes, that are in stark contrast with the rest of the "
          + "surrounding region. Directly to the south a small pier "
          + "extends into the river. Beyond that, across the river lie "
          + "the barren lands of Harondor. To the east the view is "
          + "dominated by the mountains of the Ephel Duath. The mountains rise high into "
          + "sky, forming a sinister, but majestic horizon.");

/*
    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");

    set_search_places(({"grass", "bushes"}));
    add_herb_file(HERB_DIR + "blueberry");
    add_herb_file(HERB_DIR + "blackberry");
    add_herb_file(HERB_DIR + "raspberry");
    add_herb_file(HERB_DIR + "rosemary");
    add_herb_file(HERB_DIR + "simbelmyne");
*/

/*
 * Gorboth's herb example
 */
    set_up_herbs( ({ ONE_OF_LIST(POROS_HERBS),
                     ONE_OF_LIST(POROS_HERBS),
                     ONE_OF_LIST(HERBS), }),
                         ({ "ground","grass","bushes","shrubs" }),
                  3 );


      add_exit(ITH_DIR + "poros/ford_north", "east", 0, 2);
      add_exit(ITH_DIR + "poros/p2", "west", 0, 2);

      add_item(({"path", "ground", "trail", "game trail"}), BSN(
            "The narrow walk way is little more than a game trail. It "
          + "seems to be rarely used, if at all, and is overgrown in "
          + "many places with scrub and briar."));

      add_item(({"river", "river poros", "poros"}), BSN(
            "This is the river Poros, a tributary of the mighty Anduin. "
          + "Its source lies somewhere unknown, high in the Ephel Duath. "
          + "The river itself forms the border between Ithilien to its "
          + "north, and Harondor to the south. To the southeast the "
          + "Harad Road can be seen as it crosses the river at the Fords "
          + "of the Poros just a short distance away."));

      add_item(({"bank", "river bank", "banks", "river banks", "shore",
            "northern shore", "southern shore", "river basin"}), BSN(
            "The banks of the river support a wide variety of flora, "
          + "creating a belt of greenery that mark the river's path "
          + "across the surrounding plains."));

      add_item(({"trees", "tall trees", "bushes", "green bushes",
            "greenery", "plants", "plant life", "scrub", "briar"}), BSN(
            "Trees, bushes, and other plant life flourish along "
          + "the river banks. Their close proximity to the river "
          + "provides a steady supply of water, allowing for abundant "
          + "growth in this area."));

      add_item(({"pier", "dock"}), BSN(
            "The old pier stretches out into the river. Although it "
          + "has seen better days, it is still in use to dock the boats "
          + "that carry goods and travelers up and down the river."));

      add_item(({"region", "surrounding region", "plains",
            "ithilien", "southern ithilien", "countryside"}), BSN(
            "Beyond the river basin are the plains of Southern Ithilien "
          + "to the north. Scattered woodlands and an occasional hill "
          + "dot this semi-arid land that remains largely ununhabited. "
          + "Low grass and scrub brushes are the main type of vegetation "
          + "that cover the region. Somewhere far to the west flows the "
          + "great river Anduin. While in the distance to the east "
          + "rises the Ephel Duath mountain range. Across the river to "
          + "the south is the mostly barren region of Harondor."));

      add_item(({"harondor", "south gondor"}), BSN(
            "Across the river Poros to the south lies the lands of "
          + "Harondor, or South Gondor. Harondor is mostly an arid, "
          + "barren region that consists of badlands and a desert "
          + "interior. The coastal strip and river basins are "
          + "it's only fertile and semi-fertile areas providing some "
          + "limited agricultural and grazing value."));

      add_item(({"ephel duath", "mountains", "mountain range"}), BSN(
            "The Ephel Duath, or mountains of Shadow loom in the distance. "
          + "They serve as the western and southern barriers into the "
          + "black land of Mordor. The range from this vantage has a "
          + "particularly sinister appearance, calling to mind evil "
          + "images of the Dark Lord himself."));

      add_item(({"road", "harad road", "ford", "fords",
            "fords of the poros"}), BSN(
            "Through the trees the Harad Road can be seen as it crosses "
          + "the river at the Fords of the Poros just to the southeast. "
          + "Across the Fords the road continues its way south through "
          + "Harondor, and on into the mysterious lands Harad beyond. "
          + "To the north the road winds its way onward, further into "
          + "Ithilien."));
}
