
inherit "/d/Shire/khazad/moria_room_drip";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("Cavern road");
  set_long("Large stalactites crowd the cavern ceiling, occasionaly "+
     "dripping water in places. Stalagmites likewise cover the floor "+
     "except for a wide, flat road raised on a bed of dirt and rock "+
     "cutting its way through the center of the cavern. Wet moss, "+
     "covering a great portion of the walls, glistens in the light. "+
     "The cavern road continues to the east and west.\n");

  add_item(({ "stalactites", "stalactite" }),
     "From this distance its hard to tell their exact size. Most "+
     "seem fairly large and have water streaking down their sides "+
     "from time to time.\n");
  add_item(({ "stalagmites", "stalagmite" }),
     "Some are small stumps while others tower above you. Traces "+
     "of water can be seen on most.\n");
  add_item(({ "ceiling", "roof" }),
     "It's nearly covered with stalactites.\n");
  add_item(({ "water", "drops" }),
     "Occasionally you see a small drop of water fall from above.\n");
  add_item(({ "floor", "ground" }),
     "It's covered with stalagmites except for the path of the "+
     "cavern road. In some places the ground is slick from the "+
     "water.\n");
  add_item(({ "road", "path", "cavern road", "flat road" }),
     "It's elevated a few feet above the cavern floor by a bed of "+
     "rock and dirt. It appears to be in good condition for "+
     "travelling on.\n");
  add_item(({ "wet moss", "moss" }),
     "Covering the cavern walls, it has a translucent greenish appearance "+
     "and glistens in the light.\n");
  add_item(({ "walls", "wall" }),
     "They slope outwards from the ceiling down and have moss hanging "+
     "from them.\n");
  add_exit("/d/Shire/khazad/west/cp1","west",0,1);
  add_exit("/d/Shire/khazad/west/cp3","east",0,1);
}
