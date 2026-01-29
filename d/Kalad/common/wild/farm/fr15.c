inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()

{
   ::create_room();

   hear_bell = 0;
   add_prop(ROOM_NO_TIME_DESC,1);

   set_short("Farmers Road");
   set_long("As you travel along the road it seems to be leading you "+
	    "further out of civilization and deeper into an abandoned "+
	    "waste land. You try to recognize some thing, anything that "+
	    "would point you in a direction that would lead you back to "+
	    "civilization, but to no avail all you can see in any direction "+
	    "are these spooky fields. \n");

   add_exit("/d/Kalad/common/wild/farm/fr16","west");
   add_exit("/d/Kalad/common/wild/farm/fr14","east");
}
