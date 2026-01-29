inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/lebennin/road/road.h"

void
create_area_room()
{
   set_area("south");
   set_areaname("Lebennin");
   set_land("Gondor");
   set_areatype(8);
   set_areadesc("plain");
   set_grass("green");
   
   add_exit(LEB_DIR + "road/nr18", "north", 0, 2);
   add_exit(LEB_DIR + "sroad/sr1", "south", 0, 2);
   
   add_item(({"city","pelargir", "gates", "city gates", }), BSN(
       "Pelargir upon Anduin is the second largest city of Gondor "
     + "and the largest harbour of the realm. The western city "
     + "gates are right to east of these crossroads."));
   add_item(({"crossroads", "crossroad", }), BSN(
       "Here a highway running north through eastern Lebennin "
     + "to Minas Tirith intersects with a road the goes east "
     + "into the city of Pelargir. The road coming from the "
     + "north continues south along the west bank of the Anduin "
     + "to Linhir and Dol Amroth."));
   
   set_extraline("These are crossroads just outside the western city "
     + "gates of Pelargir."
     + "\n\t\tBy order of the Steward of Gondor, the gates of "
     + "Pelargir are to remain closed until further "
     + "notice!");

   ROAD_GROUND
   remove_item("road");
   add_item(({"road"}), BSN(
       "This is an ancient well-crafted stone road that runs "
     + "through Lebennin from Minas Tirith in the north to "
     + "Pelargir in the south and Linhir in the west."));
}

