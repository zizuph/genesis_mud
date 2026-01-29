/*
 *   /d/Gondor/ithilien/poros/manor/courtyard.c
 *
 *   The courtyard of an old manor that is used as a base by corsairs.
 *
 *   Talisan,  January 1996
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/herbsearch.h"

void
create_area_room()
{
    set_land("Gondor");
    set_areaname("Ithilien");
    set_area("southern");
    set_areadesc("courtyard");
    set_areatype(0);

    set_extraline("The courtyard is surrounded by a old crumbling wall "
      + "that is collapsed in many areas. Weeds "
      + "and scrub, along with rubble litter the ground here. To the "
      + "northwest a low, wide flight of stairs leads up to a pair "
      + "of broken doors. And to the east, over a fallen rusting gate, "
      + "leads out of the courtyard.");

    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");

    set_search_places(({"grass", "weeds", "bushes", "scrub"}));
    /* reduced the herbs. this is a bare, scrubby courtyard, not the 
     * forests of ithilien. 
     * also, morgurth grows only in mordor and the morgul vale,
     * and may not be used elsewhere.  gnadnar 1998
     */
    set_search_places(({"grass", "weeds", "bushes", "scrub"}));
    add_herb_file(HERB_DIR + "redweed");
    add_herb_file(HERB_DIR + "blackberry");
    add_herb_file(HERB_DIR + "braspberry");

    add_exit(POROS_DIR + "manor/foyer", "northwest", 0, 1);
    add_exit(POROS_DIR + "p9", "east", 0, 2);

    add_item(({"courtyard", "ground"}), BSN(
        "The courtyard, as with the rest of the ruined manor, looks "
      + "as if it has been abandoned for centuries."));

    add_item(({"wall", "old wall", "collapsed wall"}), BSN(
        "The old wall is crumbling, and collapsed in many areas. You "
      + "can see rubble from the wall lying in many places within "
      + "the courtyard."));

    add_item(({"rubble"}), BSN(
        "Rubble from the collapsed wall, and old manor are scattered "
      + "about the courtyard."));

    add_item(({"stairs", "steps"}), BSN(
        "The flight of stone steps leads from the courtyard up to the "
      + "manor house. As with the rest of the courtyard, the steps "
      + "are overgrown with weeds, and crumbling in many areas."));

    add_item(({"gate", "rusting gate"}), BSN(
        "The once sturdy iron gate now lies twisted and rusting on the "
      + "ground at the end of the courtyard. You determine they were "
      + "apparently battered in at one time long ago, and left lying "
      + "undisturbed since."));

    add_item(({"weeds", "scrub"}), BSN(
        "Weeds and scrub grow undisturbed all throughout the courtyard."));

    add_item(({"manor", "ruins", "manor house", "house"}), BSN(
        "Over time the elements have taken their toll on the "
      + "old manor house, causing the collapse of the structure "
      + "in many places. The manor, once home to a Dunadan Lord, "
      + "seems to have been uninhabited for centuries."));

    add_item(({"door", "doors", "broken doors", "broken door"}), BSN(
        "The once sturdy doors lie broken, and fragmented in the "
      + "doorway to the manor, at the top of the stairs."));
}
