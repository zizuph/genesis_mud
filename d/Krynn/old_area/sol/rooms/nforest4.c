/* Forest coded by Lord Rastlin */
/* modified by Teth, Feb.13,96  */

#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit FOROUTROOM;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"mixedforest",}));

#define STMON "/d/Krynn/solace/village/monster/"

object wildlife;

void
reset_solace_room()
{
   if (!wildlife) {
      wildlife = random(10) > 5 ? clone_object(STMON+"skunk") : clone_object(STMON+"squirrel");
      wildlife->move(TO);
   }
    set_searched(random(2));

}

void
create_solace_room()
{
    set_place(FOREST);

    set_long_desc("These are foothills of the Sentinel Peaks mountain range. " +
      "A well-used trail runs northeast into a hilly rocky area, while " +
      "in the southwest direction, it returns to more forest. Tiny bushes " +
      "line the trail, but they gradually disappear as one heads northeast. " +
      "The trail is covered with footprints, that seem to be from a two-" +
      "legged animal or animals. There aren't any trees here.");
    add_item(({"foothills","hills","mountain range","mountains",
               "Sentinel Peaks", "sentinel peaks", "Peaks", "peaks"}),
               "These surround you, giving the area a measure of " +
               "distinction.\n");
    add_item("terrain", "It is somewhat hilly, caused by this area's " +
             "location in the Sentinel Peaks mountain range.\n");
    add_item("bush", "There are many of them, you'd be better off to look " +
             "at all of them.\n");
    add_item("bushes", "These scrubby bushes line the trail. Blueberry and " +
             "other heath-like herbs are best found here!\n");
    add_item("trail", "It's covered with footprints. You'd have to go " +
             "northeast perhaps to see what caused them!\n");
    add_item("footprints", "They belong to some two-legged creature, of " +
             "human size or so.\n");
    add_exit(TDIR + "nforest2", "southwest");
    add_exit(TDIR + "hill1", "northeast");
   
    seteuid(getuid(TO));
    set_up_herbs(({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs)}), ({"bushes","trail",}), 2);
       OUTSIDE;  /* An outside room */
   
    set_alarm(1.0,0.0,"reset_room");
}

