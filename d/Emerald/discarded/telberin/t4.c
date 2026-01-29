inherit "/std/room";

#include "default.h"

void
create_room()
{
   set_short("Temple of Erarra");
   set_long("This beautifully archaic building, constructed " +
            "many centuries ago, is home to the Order of the Goddess "+
            "of Healing. It is magnificently built of blue marble "+
            "and the light from the windows above floods in like the "+
            "Angels of Heaven. There is an altar here.\n");
   
   add_exit(THIS_DIR + "t1", "south");
   
   add_item("marble", "The marble is beautifully blue, a light sky blue.\n");
   add_item("windows", "The windows are skylights in the roof.\n");
   add_item("altar", "The altar is of the purest white marble, perfect in " +
            "its design.\n");
}
