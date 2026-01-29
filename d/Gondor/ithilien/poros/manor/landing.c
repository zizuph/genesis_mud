/*
 *   /d/Gondor/ithilien/poros/manor/landing.c
 *
 *   The hidden landing where the corsairs dock their ship at the manor.
 *
 *   Talisan,  January 1996
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/herbsearch.h"
#include "/d/Gondor/common/lib/herb_list.h"
#include "/d/Gondor/ithilien/poros/poros_herbs.h"

static object  corsair;

public void
reset_room()
{
    if (!objectp(corsair))
    {
      corsair = clone_object(POROS_DIR + "npcs/corsair");
      corsair->arm_me();
      corsair->move_living("down", TO);
    }
}

void
create_area_room()
{
    set_land("Gondor");
    set_areaname("Ithilien");
    set_area("southern");
    set_areadesc("landing");
    set_areatype(0);

    set_extraline("A newly built pier stretches out into an old canal, and "
      + "creates a boat landing here. To the northeast a flight of "
      + "stairs leads up to a small terraced garden area.");

    /* deleted herbs. i don't believe they would grow on a pier
     * gnadnar 1998
     */

    add_exit(POROS_DIR + "manor/garden", "northeast", 0, 1);

    add_item(({"pier", "new pier"}), BSN(
        "You can tell that the pier has only recently been built. However "
      + "some signs show that a much older pier may have once stood here "
      + "as well. The pier seems stable, and capable of docking a fairly "
      + "large river boat."));

    add_item(({"canal", "old canal"}), BSN(
        "The old canal looks as if it has been re-dredged not too long ago. "
      + "You guess it was once used by the local Lord, and now the corsairs "
      + "to access the nearby Poros river, and the Anduin beyond."));

    add_item(({"landing", "ground", "boat landing"}), BSN(
        "This is where the corsairs dock their ship while at their base. "
      + "No ship is here now, so you figure some of the corsairs must "
      + "be out on a raid somewhere."));

    add_item(({"stairs", "old stairs"}), BSN(
        "You notice the stairs are old and worn, much so like the rest"
      + " of the old manor."));

    reset_room();

}

