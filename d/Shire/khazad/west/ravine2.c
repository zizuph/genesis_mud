
inherit "/d/Shire/common/lib/rom";
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("In a ravine");
  set_long("A small trickle of water makes its way down this slick, "+
     "stone channel. The walls of the ravine reach high "+
     "above your head here. Stalagmites line the top "+
     "of the ravine walls effectively fencing everything in. The "+
     "ravine deepens to the east and climbs to the "+
     "southwest.\n");

   add_item(({ "stalactites", "stalactite" }),
     "From this distance its hard to tell their exact size. Most "+
     "seem fairly large and have water streaking down their sides "+
     "from time to time.\n");
  add_item(({ "stalagmites", "stalagmite" }),
     "Some are small stumps while others tower above you. Traces "+
     "of water can be seen on most.\n");
  add_item("stumps",
     "Small stalagmites, nothing spectacular about them.\n");
  add_item("ravine",
     "It gradually deepens to the east and ascends to the "+
     "southwest.\n");
  add_exit("/d/Shire/khazad/west/ravine1","southwest",0,1);
  add_exit("/d/Shire/khazad/west/ravine3","east",0,1);
}
