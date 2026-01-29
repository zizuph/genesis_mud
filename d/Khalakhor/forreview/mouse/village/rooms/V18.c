/* a room coded by Elizabeth Cook/Mouse, February 1997 */

inherit "std/room";
#include <stdproperties.h>
#include "../../mouse.h"

void create_room()  {
     set_short("Crossing a bridge");
     set_long("   This is a stone bridge crossing the Festiwycke Creek. "+
          "Peering over the side, you can see the water flowing downstream "+
          "to the southeast. Gently sloping ravine walls rise above the "+
          "creek bed. The road bends out of sight very quickly at either "+
          "end of the bridge, leaving you with a strange sense of isolation. "+
          "The soothing sound of the water comforts you.\n");
     add_exit(ROOT+"village/rooms/V19","northeast");
     add_exit(ROOT+"village/rooms/V17","southwest");

}

