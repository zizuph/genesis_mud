inherit "/d/Gondor/common/room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

object door;

create_room()
{
  set_short("On the porch of the tomb of the Stewards");
  set_long("You are on top of the porch before the stone door of the\n"+
    "House of the Stewards. Stone stairs lined by many-pillared balusters\n"+
    "lead down south into Rath Dinen, across which is the House of the\n"+
    "Kings. These are the Hallows, the mansions of the dead kings and\n"+
    "their stewards.\n");
  add_item("stairs","The stairs are made of pale grey stone.\n");
  add_item("porch","The porch is not large, but wide enough so that those\n"+
    "who carry the bier can stand there while the door is opened.\n");
  add_item("house","The stone building gives every impression of being empty\n"+
    "but inside are the remains of all Stewards of Gondor, from Pelendur\n"+
    "the First Steward, to Ecthelion II, father of the current Ruling\n"+
    "Steward of Gondor, Denethor II.\n");
  clone_object(MINAS_DIR+"obj/stew_door_out")->move(TO);
  add_exit(MINAS_DIR+"houses/rath_dinen","south",0,0);
}
