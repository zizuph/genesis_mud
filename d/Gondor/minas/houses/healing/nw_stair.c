inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#define TRUSTED_IN_HOH   "_trusted_in_houses_of_healing"

create_room()
{
  set_short("The stairway in the west wing of the Houses of Healing");
  set_long(BSN("The corridor runs west and west here, in the east wing of "+
    "the House. In the south and north walls windows are letting fresh air "+
    "in, and there is a stairway leading up. The white-walled corridor "+
    "looks clean and well kept."));
  add_item(({"window","garden","windows"}),BSN(
    "Outside you see a green garden behind the Houses of Healing."));
    add_prop(ROOM_I_INSIDE,1);
  add_exit(HOH_DIR + "main_entr","east",0,0);
  add_exit(HOH_DIR + "nw_corr","west",0,0);
  add_exit(HOH_DIR + "nw_upstair","up",0,2);
}

check_guards()
{
  object guard;
  if (!present("guard")) return 0;
  guard = present("guard");
  if (CAN_SEE(guard, TP) && CAN_SEE_IN_ROOM(guard) &&
    !TP->query_prop(TRUSTED_IN_HOH)) {
    TP->catch_msg("The guard blocks the doorway.\n");
    guard->command("say Noone is allowed to enter that room.");
    return 1;
    }
  return 0;
}

