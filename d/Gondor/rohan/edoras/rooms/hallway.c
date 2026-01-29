inherit "/d/Gondor/common/room";
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

object door2, gate;

void
create_room()
{
  set_short("A hallway in a barracks building");
  set_long(BS("You are in a large hallway inside a building which looks like a typical "+
    "example of military barracks. The stone floor has seen much use from heavy boots, "+
    "but is in good repair and has been swept clean recently. The walls are made of roughly "+
    "hewn stone boulders and nothing has been done to adorn them. The only interruption are "+
    "some banners to the right of the door in the western wall. \n"));
  add_item(({"banner","banners"}),BS("The largest of these banners shows a riderless horse galloping over a field of green. "+
  	"In the lower right corner there stands a golden 'T'. You identify the banner as the standard of the King's Eored of the "+
  	"riders of Rohan.\n"));
  door2 = clone_object(EDORAS_DIR + "rooms/bhw2door");
  door2->move(TO);
  gate = clone_object(EDORAS_DIR + "rooms/barrgate");
  gate->move(TO);
  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_LIGHT,1);
  add_exit("/d/Gondor/rohan/edoras/rooms/bhallway2", "east", 0, 1);
}
