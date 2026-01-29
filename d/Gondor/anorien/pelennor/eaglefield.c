inherit "/d/Gondor/elessar/lib/field";
#include "/d/Gondor/defs.h"

create_room()
{
  areatype = 1;
  areadesc = "green field";
  area = "central";
  areaname = "Anorien";
  land = "Gondor";
  grass = "green, juicy ";
  extraline = "The sloping terrain makes it difficult to see much around you, "+
    "but you think you see a cobbled road further to the east. The fields "+
    "stretch out to the north and east. In the ground you see some strange marks, "+
    "as if large claws have scraped and torn the grass here.";
  add_item("marks","You would guess they were made by large claws.\n");
  add_item("ground",BSN("The sloping fields here are no less green with "
    + "grass than the more level fields to the east. Some strange "
    + "marks are visible in the ground, as if something with "
    + "large claws has torn the grass here"));
  add_exit("/d/Gondor/anorien/road/wr3","east",0,2);
  make_the_room();
}

