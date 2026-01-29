/*
 * Daenbraigh smithy
 * TAPAKAH, 09/2005
 */

inherit "/d/Khalakhor/std/room";

#include <stdproperties.h>
#include "../../nspeir.h";
#include "../../village/village.h";

object smith;

void
create_khalakhor_room()
{
  set_short("Daenbraigh smithy");
  set_long(BS("The smithy is set by a renegade dwarf. There is a plaque on the wall.\n"));

  add_item(({"plaque"}),
	   BSN("You can repair your weapons here, if the smith is present."+
	       "You can also inquiry how much the repair will <cost> you.\n");
  add_prop(ROOM_I_INSIDE,1);
  add_prop(GV_OUTSIDE, 0);
  add_exit("ns_2","west");
}
void
reset_room() {

  ::reset_room();

  if(! smith) {
    smith = clone_object(SMITH);
    smith->move(TO);
  }
}
