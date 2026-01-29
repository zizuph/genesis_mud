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
  	+"south you see a dim light and what appears to be a room, "
  	+"while back to the north lies the gith encampment.  Dust "
  	+"covers the floor here, obviously disturbed by much "
  	+"traffic.  The one strange thing you do notice here is that "
  	+"there is the faintest hint of moisture in the air.\n");
  add_item("dust","There is quite a bit of Athas's trademark brown "
  	+"dust here, it is mostly in small piles against the walls, "
  	+"though.\n");
  add_exit(CAMP + "c26","southwest");
  add_exit(CAMP + "c22","north");
}

