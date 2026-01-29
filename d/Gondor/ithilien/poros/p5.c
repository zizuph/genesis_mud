/*
 *   /d/Gondor/ithilien/poros/p5.c
 *
 *   This area is part of a path that leads from the Harad Road to a
 *   hidden Corsair base in Southern Ithilien, along the Poros river.
 *   This particular area hides the path that leads to the base, while
 *   a decoy path leads farther into the interior of Ithilien.
 *
 *   Talisan,  December 1995
 *
 *   Typo and format corrections October 2001, Serif.
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/herb_list.h"
#include "/d/Gondor/ithilien/poros/poros_herbs.h"

void  enter_bushes();

void
create_area_room()
{
    set_land("Gondor");
    set_areaname("Ithilien");
    set_area("southern");
    set_areadesc("path");
    set_areatype(1);

    set_extraline("The narrow path is now inland from the river Poros, "
        + "in an area dominated by scrub bushes and briar. A large rock "
        + "stands here, almost completely covered by the thick growth. "
        + "Along the eastern horizon the mountains of the Ephel Duath loom "
        + "ominously in the distance.");

    set_up_herbs( ({ ONE_OF_LIST(POROS_GOOD_HERBS),
                     ONE_OF_LIST(POROS_GOOD_HERBS),
                     ONE_OF_LIST(POROS_GOOD_HERBS),
                     ONE_OF_LIST(POROS_GOOD_HERBS), }),
        ({"ground", "grass", "bushes"}), 4 );

    add_exit(ITH_DIR + "poros/p10", "west", 0, 2);
    add_exit(ITH_DIR + "poros/p4", "east", 0, 2);

    add_item(({"path", "ground", "trail", "game trail"}), 
        "The narrow walk way is little more than a game trail. It seems "
      + "to be rarely used, if at all, and is overgrown in many places "
      + "with scrub and briar.\n");

    add_item(({"bushes", "scrub", "scrub bushes", "briar", "trees",
        "plants", "plant life", "vegetation", "growth", "thick growth",
        "brush"}), 
        "The bushes in this area are especially thick, making movement "
      + "difficult without getting snagged by briar. An occasional small "
      + "group of trees can be seen out across the surrounding "
      + "countryside.\n");

    add_item(({"region", "surrounding region", "plains", "ithilien",
        "southern ithilien", "countryside", "surrounding countryside"}), 
        "Scattered woodlands and an occasional hill dot this semi-arid "
      + "land that remains largely uninhabited. Low grass and scrub brushes "
      + "are the main type of vegetation that cover the region. Somewhere "
      + "far to the west lies the great river Anduin, while in the "
      + "distance to the east rises the Ephel Duath mountain range. "
      + "Across the river to the south is the mostly barren region "
      + "of Harondor.\n");

    add_item(({"ephel duath", "mountains", "mountain range"}), 
        "The Ephel Duath, or Mountains of Shadow loom in the distance. "
      + "They serve as the western and southern barriers into the black "
      + "land of Mordor to the east. The range from this vantage has a "
      + "particularly sinister appearence calling to mind evil images of "
      + "the Dark Lord himself.\n");

    add_item(({"rock", "large rock", "statue", "worn statue"}), 
        "Upon closer inspection of the rock you notice that it is in "
      + "fact an ancient worn statue. Despite severe erosion, the form "
      + "of a Dunadan Lord can be made out of the rock. Armed and armoured "
      + "in ancient fashion, a crescent moon is engraved on the figure's "
      + "shield.\n");

    add_cmd_item(({"bush", "bushes", "the bushes"}), "enter", 
        "@@enter_bushes");
}

int
enter_bushes()
{
    if (TP->resolve_task(TASK_ROUTINE, ({TS_STR, SS_AWARENESS})))
    {
      write("As you enter the bushes to the southwest, you step onto "
          + "a hidden path.\n");
      TP->move_living("into the bushes", ITH_DIR + "poros/p6");
      return 1;
    }

    else
    write("As you move into the thick bushes, you become tangled up "
      + "in the briar and can barely move.\n");
    say(QCTNAME(TP)+" trys to walk into the bushes but becomes "
      + "hoplessly entangled in the prickly briar.\n");
    return 0;
}
