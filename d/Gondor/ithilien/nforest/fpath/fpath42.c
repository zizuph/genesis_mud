#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("green-shadowed woodlands");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("oak");
    set_extraline("You are walking under old trees in ever-green woods. "
      + "The woodlands seem to extend forever in every direction, but "
      + "they are growing thinner to the west. In that direction, light "
    + "is shining through the trees, as if the forest ended here. "
      + "An ever-present sweet and pungent smell of "
      + "herbs and flowers dominates in Ithilien, the garden of Gondor.");
    set_up_herbs( ({ ONE_OF_LIST(HERB_MASTER->query_herbs("ithilien")),
                     ONE_OF_LIST(HERB_MASTER->query_herbs("forest")),
                     HERB_DIR + "myrtle", }),
                  ({"ground","field","flowers","forest"}), 3);
    add_item(({"mountains","mountain-range","mountain","ephel duath"}),BS(
        "From here the mountains in the east are hidden by many tree tops.\n"));
    add_item(({"forest","wood","woodlands","herbs"}), "Many great trees "
      + "are growing here, cedars and giant oaks and hoary ash trees.\n");
    add_exit(ITH_DIR + "nforest/fpath/fpath41",  "northeast", 0, 4);
    add_exit(ITH_DIR + "nforest/forest2",        "west",      0, 4);

}

string
short_desc()
{
  return CAP(areadesc) + " in the forests of " + CAP(area) + " " + areaname;
}

