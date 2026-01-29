#include "defs.h"

CONSTRUCT_ROOM {
   set_short("Queen's ballroom");
   set_long("You are standing on the marble floor in the Queen's ballroom. "+
      "It is criss-crossed with cracks and holes, and it is covered "+
      "with dark blotches. Great pillars and stairs reaches up toward "+
      "the gallery. The ballroom extends north-, south- and "+
      "westwards. To the west there is a platform.\n");
   add_item(({"floor","cracks","holes","blotches"}),
      "You won't fall into them.");
   add_item("pillars",
      "Great winding pillars they are. They lead all up to the "+
      "ceiling, which is about 20 yards over you. However, they are "+
      "made in marble, so you can't climb them.");
   add_item("stairs","They will lead up to the overlooking gallery.");
   UP("gallery");
   SOUTH("ballrs");
   NORTH("ballrn");
   WEST("ballrw");
}



