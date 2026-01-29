inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/common/defs.h"
#include "defs.h"


void
create_room()
 {
  set_short("Mountain Passage");
  set_long("You are in the middle of a dark stone passage.  To the "
  	+"south the passage curves away from you, "
  	+"while back to the north lies the gith encampment.  Dust "
  	+"covers the floor here, obviously disturbed by much "
  	+"traffic.  The walls around you look to have been shaped "
  	+"carefully by craftsman, and not dug randomly by some less "
  	+"skilled person.  "
  	+"The one strange thing you do notice here is that "
  	+"there is the faintest hint of moisture in the air.\n");
  add_item("dust","There is quite a bit of Athas's trademark brown "
  	+"dust here, it is mostly in small piles against the walls, "
  	+"though.\n");
  add_item("walls","They are crafted expertly from the rock around "
  	+"you, and lead deeper into the mountain.  Some wooden "
  	+"panelling is covering most of the rock here to make things "
  	+"look slightly more pleasing to the eye.\n");
  add_item("panelling","It is made of some form of thin imitation "
  	+"wood and covers the walls of this room.\n");

  add_exit(CAMP + "c25","south");
  add_exit(CAMP + "c16","northeast");
}

