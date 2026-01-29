/* a room coded by Elizabeth Cook/Mouse, February 1997 */

inherit "std/room";
#include <stdproperties.h>
#include "../../mouse.h"

void create_room()  {
     set_short("Beside a bridge");
     set_long("   As you approach the bend, it becomes obvious that "+
          "Festiwycke Road terminates at a junction a short distance "+
          "to the north. You can hear the enchantingly refreshing sound "+
          "of water flowing beneath the bridge leading southwest. Birds "+
          "flitter and sing in the trees above. An indefinable feeling of "+
          "peace and contentment seems to fill the air.\n");
     add_exit(ROOT+"mansion/rooms/P1","north");
     add_exit(ROOT+"village/rooms/V18","southwest");

}

