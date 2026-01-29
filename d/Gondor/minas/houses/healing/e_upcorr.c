inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#define TRUSTED_IN_HOH   "_trusted_in_houses_of_healing"

create_room()
{
  set_short("The upper corridors in the east wing of the Houses of Healing");
  set_long(BSN("The corridor runs north and south here, in the east wing of "+
    "the House. In the west wall windows are letting fresh air "+
    "in, and there is a doorway to the east. The white-walled corridor "+
    "leads north to an archway, while other rooms are accessible to "+
    "the south."));
  add_item(({"window","garden","windows"}),BSN(
    "Outside you see a green garden behind the Houses of Healing."));
  add_item(({"east doorway","doorway"}),BSN("A doorway opens "+
    "in the east wall. Above it, you read the words:\n"+
    "      Surgeon Haldira    -   Scar Removal."));
  add_prop(ROOM_I_INSIDE,1);
  add_exit(HOH_DIR + "se_upcorr","south",0,0);
  add_exit(HOH_DIR + "ne_upstair","north",0,0);
  add_exit(HOH_DIR + "surgeon_waiting","east",0,0);
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

