
inherit "/std/door";
#include "../domain.h"
#include <stdproperties.h>

void
create_door()
{

  set_door_id("easternhallwaydoors");
  set_door_name(({"east doors","doors","double doors"}));
  set_door_desc(BS("Carved from the same stone as the rest of this cavern, " +
  "stands a set of double doors leading to the east. Set side to side, no amount " +
  "of light or sound penetrates the solidity of their figure.\n"));
  set_other_room("/d/Calia/lasayr/e_hall");
  set_open(0);
  set_locked(0);
  set_pass_command(({"e","east"}));
  set_fail_pass("The doors to your east are unwilling to move out of the way.\n");
  set_open_desc("A passage to the east lies open.\n");
  set_open_command(({"pull","open"}));
  set_open_mess(({"pulls on the east doors, they swing silently aside.\n","The " +
  "doors to the west move easily aside.\n"}));
  set_fail_open("The east doors hold to the side to allow passage already.\n");
  set_closed_desc("To the east, the large double doors lay closed.\n");
  set_close_command(({"push","close"}));
  set_close_mess(({"pushes on the east doors, they swing silently shut.\n","The " +
  "doors to the west silently close.\n"}));
  set_fail_close("The east doors are already closed.\n");

  add_prop(DOOR_I_HEIGHT, 400);
  add_prop(OBJ_I_WEIGHT, 1000000);
  add_prop(OBJ_I_VOLUME, 40000);

}
