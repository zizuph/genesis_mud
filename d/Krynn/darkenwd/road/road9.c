/* Road9 coded by Teth
 * March 4, 1996
 * Last updated Oct 26, 1996
 */

#include "local.h"

inherit ROADOUT;

inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"urban","mixedforest",}));

#define HAVEN_ROAD "/d/Krynn/haven/road/mount_road3"

void
reset_darkenwd_room()
{
    set_searched(random(2));
}

void
create_darkenwd_room()
{
    set_place(ROAD);

    set_long_desc("This road runs between the village of Solace to the " +
      "east and the town of Haven to the west, through Sentinel Gap. It " +
      "passes through the Sentinel Peaks mountain range, a collection of " +
      "eroded hills and older mountains. The Twin Peaks of Tasin and " +
      "Fasin loom to the north and south respectively. A few herbs and " +
      "shrubs line the road.");
    add_item(({"herbs", "shrubs"}), "They appear to contain some useful " +
      "herbs.\n");
    add_item("road", "The road is covered with large rocks and stones, " +
      "little of interest to one as travelled as you.\n");
    add_item(({"stones","rocks", "large rocks"}), "They are grey, with the " +
      "occasional one having a mottled black pattern.\n");
    add_item(({"Twin Peaks", "twin peaks", "peaks", "Peaks"}), "The Twin " +
      "Peaks stand guard over Sentinel Gap, the only pass nearby " +
      "through the mountains.\n");
    add_item(({"pass", "Gap", "gap", "sentinel gap", "Sentinel Gap"}), "This "+
      "pass cuts through the Sentinel Peaks mountain range, between " +
      "Haven and Solace.\n");
    add_item(({"Sentinel Peaks", "sentinel peaks", "mountains",
        "mountain range"}), "This mountain range is the cause of " +
      "the rolling topography, you astutely guess.\n");
    add_item("mountain", "Which mountain?\n");
    add_item(({"tasin", "Tasin", "first mountain"}), "To the north stands " +
      "Tasin, one of the Twin Peaks. It is coloured a dusky grey.\n");
    add_item(({"fasin", "Fasin", "second mountain"}), "Fasin stands in the " +
      "south, its rock a foggy grey. It is one of the Twin Peaks.\n");
    add_exit(TDIR + "road8", "east",0,3);
    add_exit(HAV_ROAD + "mount_road3", "west", 0, 2);

    seteuid(getuid(TO));
    set_up_herbs( ({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({"bushes","herbs",}), 1);
    OUTSIDE;  /* An outside room */

    reset_darkenwd_room();

}

int
closed()
{
    write("Unfortunately, the road pass to Twin Peaks Vale is " +
      "closed. Sentinel Gap appears to be roadblocked for now. " +
      "You'll have to go back where you came from.\n");
    return 1;
}


