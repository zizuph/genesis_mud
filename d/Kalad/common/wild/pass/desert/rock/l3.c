inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   add_prop(ROOM_S_DARK_LONG,"A dark, moist location.\n");
   set_short("A dark tunnelway");
   set_long("This is a damp tunnel located somewhere beneath the life-giving "+
      "spring in the rock plains above you. Some of the water from above "+
      "has trickled down here and has formed a rather moist and cool "+
      "environment. Several mosses can be seen growing all over this "+
      "tunnel, which heads to the north and south.\n");
   add_item(({"damp tunnelway","tunnelway","tunnel"}),
      "A moisture-ridden underground passage.\n");
   add_item(({"water"}),
      "Surprisingly cool, it has created a moist cool environment here "+
      "where mosses can grow.\n");
   add_item(({"mosses","moss"}),
      "Green and clammy to the touch, they cover the walls and ceiling of "+
      "this tunnel.\n");
   add_item(({"walls","wall","ceiling","floor","ground"}),
      "The interior of this passage is composed of an extremely dense, "+
      "black rock, quite dissimilar to the composition of the many rocks "+
      "that lie on the rock plains above.\n");
   add_exit(CPASS(desert/rock/l4),"north");
   add_exit(CPASS(desert/rock/l2),"south");
}
