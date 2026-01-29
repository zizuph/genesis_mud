/* room coded by Elizabeth Cook/Mouse, January 1997 */

inherit "std/room";
#include <stdproperties.h> 
inherit "/d/Gondor/open/HERBS/herbsearch";
#include "../../mouse.h"    

int searched;  

void create_room()  {
     set_short("On the trader's lane");
     set_long("   A low stone wall laden with wild roses separates the "+
          "cobbled lane from houses of stone to the south. A wooden gate "+
          "is set in the wall to the southwest. On the other "+
          "side of the lane is the trader's comfortable timber and stuccoed "+
          "home. Adjacent to his large house is the trader's shop, directly "+
          "to the west. Two burly men are unloading a wagon at a platform "+
          "to the side of the shop entrance.\n");

     room_add_object(ROOT+"village/items/rosegate.c");  

     add_exit(ROOT+"village/rooms/V8","northeast");
     add_exit(ROOT+"village/rooms/shop","west");

     set_up_herbs(({ROOT+"herbs/yarrow", ROOT+"herbs/elecampane",
                    ROOT+"herbs/aconite"}), 
                    ({"ditch"}));
     places = ({"ditch"});
     
}

  


