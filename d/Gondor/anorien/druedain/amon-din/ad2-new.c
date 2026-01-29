inherit "/d/Gondor/common/lib/area_room";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/herb_list.h"

void
create_area_room()
{
    set_areatype(7);
    set_areadesc("clearing");
    set_area("central");
    set_areaname("Anorien");
/*
  set_short("in a small clearing at the base of Amon Din");
*/
  set_extraline(
    "The trees and vegetation have fallen away here to allow for a small " +
    "clearing. You stand at the base of Amon Din, which rises before you " +
    "directly to the north. A small path makes its way up the hill to the " +
    "northwest where the trees once again resume growth.");
    add_item(({"hill","amon din"}), BSN(
      "Tall and silent, the mount of Amon Din dwarfs all in the immediate " +
      "area. For many years it has stood as the closest beacon hill to the " +
      "Rammas Echor, serving as a signal for allied reinforcement in times " +
      "of great need. Only the very top of the hill is bare, and a small " +
      "building is visible upon the leveled peak."));
    add_item(({"path"}), BSN(
      "The path winds its way up the slope and disappears amongst the trees " +
      "to the northwest."));
    add_item(({"peak","building","top"}), BSN(
      "Still far below the peak of Amon Din, you are able to see little " +
      "detail of its contents. It is clear that there is some form of " +
      "human force at work there, but you cannot see precisely what it is."));
    add_item(({"clearing","ground"}), BSN(
      "Not more than thirty feet in circumference, this small grassy " +
      "clearing provides for both sunlight and moisture and seems very well " +
      "nourished. Sloping gradually steeper at the base of the hill, the " +
      "ground grows thicker with trees and bushes and a path leads out of " +
      "the clearing to the northwest."));
    add_item(({"trees"}), BSN(
      "The side of the hill is covered with trees which grow thinner with " +
      "elevation. The nearest ones are a good fifteen paces away."));
    add_exit(ANO_DIR + "druedain/amon-din/ad1","northeast", 0, 2);
    add_exit(ANO_DIR + "druedain/amon-din/ad3","northwest", 0, 2);

    set_up_herbs( ({ HERB_DIR + "coccinea",
                     ONE_OF_LIST(HERBS), ONE_OF_LIST(HERBS), }),
                          ({ "ground","clearing", }),
                  3 );

}

