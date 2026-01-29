inherit "/d/Gondor/common/room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

object door;

create_room()
{
  set_short("On the porch of the tomb of the Kings");
  set_long(BSN("You are on the porch before the stone door of the "+
    "House of the Kings. Stone stairs lined by many-pillared balusters "+
    "lead down north into the Rath Dinen, across which is the House of the "+
    "Stewards. There is a sanctified silence to the Hallows, the mansions "+
    "of the dead kings and their stewards."));
  add_item("stairs","The stairs are made of pale grey stone.\n");
  add_item("porch","The porch is not large, but wide enough so that those\n"+
    "who carry the bier can stand there while the door is opened.\n");
  add_item("house",BSN("The stone building gives every impression of being empty "+
    "but inside are the remains of all Kings of Gondor, from Meneldil, "+
    "the son of Anarion, to Earnil II, father of Earnur, last King of "+
    "Gondor."));
  clone_object(MINAS_DIR+"obj/king_door_out")->move(TO);
  add_exit(MINAS_DIR+"houses/rath_dinen","north",0,0);
}
