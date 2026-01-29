/*  The link between Gondor and the Shire  */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_area("central");
    set_areaname("Cardolan");
    set_areatype(8);
    set_land("the lost realm of Arnor");
    set_areadesc("hilly countryside");
    set_grass("green");
    set_treetype("holly");
    set_extraline("You are on an old dusty road, long since fallen into disrepair. "+
    "All around you is the hilly landscape of Cardolan, green rolling hills "+
    "in every direction. The forgotten road continues far towards the "+
    "northwestern horizon, while creeping across a hill to the southeast. "+
    "You have a feeling that the northwest way might take you for a long "+
      "journey.");
  add_exit("/d/Shire/common/gondorlink","northwest",0,5);
  add_exit(CARD_DIR+"road/r36","southeast",0,5);
}

