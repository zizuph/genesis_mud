inherit "/std/room";

#include "default.h"
#include <stdproperties.h>

void
create_room()
{
   set_short("First floor");
   set_long("You are standing in the hallway of the first floor, rooms to " +
            "the east and northwest. The walls are all painted in the latest" +
            " styles, and the floor is covered by an expensive carpet. The " +
            "grand staircase leads down to the entrance to this house.\n");
   
   add_prop(ROOM_I_INSIDE, 1);
   add_exit(THIS_DIR + "up3", "east");
   add_exit(THIS_DIR + "up2","northwest");
   add_exit(THIS_DIR + "house1","down");
   
   add_item("entrance","The entrance leads out into the city.\n");
   add_item("walls","The walls are all painted in two, the bottom half "+
        "painted dark brown and the top half painted with light yellow "+
        "stripes.\n");
   add_item(({"floor","carpet"}),"The floor is covered by a beautiful "+
        "patterned yellow carpet, to match the decorated walls.\n");
   add_item("staircase","The staircase is grand, a good eight feet wide "+
        "and slowly winding it's way down to the ground floor.\n");   
}
