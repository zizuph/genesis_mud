
inherit "/std/door";
#include "../domain.h"
#include <stdproperties.h>

void
create_door()
{

  set_door_id("westernhallwaydoors");
  set_door_name(({"west doors","doors","double doors"}));
  set_door_desc(BS("Carved from the same stone as the rest of this cavern, " +
  "stands a set of double doors leading to the west. Set side to side, no amount " +
  "of light or sound penetrates the solidity of their figure.\n"));
  set_other_room("/d/Calia/lasayr/w_hall");
  set_open(0);
  set_locked(0);
  set_pass_command(({"w","west"}));
  set_fail_pass("The doors to your west are unwilling to move out of the way.\n");
  set_open_desc("A passage to the west lies open.\n");
  set_open_command(({"pull","open"}));
  set_open_mess(({"pulls on the west doors, they swing silently aside.\n","The " +
  "doors to the east move easily aside.\n"}));
  set_fail_open("The west doors hold to the side to allow passage already.\n");
  set_closed_desc("To the west, the large double doors lay closed.\n");
  set_close_command(({"push","close"}));
  set_close_mess(({"pushes on the west doors, they swing silently shut.\n","The " +
  "doors to the east silently close.\n"}));
  set_fail_close("The west doors are already closed.\n");

  add_prop(DOOR_I_HEIGHT, 400);
  add_prop(OBJ_I_WEIGHT, 1000000);
  add_prop(OBJ_I_VOLUME, 40000);

}
