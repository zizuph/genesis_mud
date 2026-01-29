inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#define TRUSTED_IN_HOH   "_trusted_in_houses_of_healing"

create_room()
{
  set_short("The top of the east stairs in the Houses of Healing");
  set_long(BSN("You are standing at the top of the stairs. White "+
    "steps of stone descend down west to the ground floor. "+
    "Through an archway to the south, another corridor can be "+
    "seen, with doorways along the left wall. Towards the west, "+
    "passing the stairs, the main corridor stretches out. "+
    "Large tapestries meet the eyes of those who come up the stairs."));
  add_item(({"window","garden","windows"}),BSN(
    "Outside you see a green garden behind the Houses of Healing."));
  add_item("corridor",BSN("The main corridor runs in a westward direction, white "+
    "walls with glass windows at set intervals lining it. "+
    "A southward corridor starts beyond an archway in the south wall. "+
    "Along it you see doorways, probably leading into chambers of "+
    "healing or resting."));
  add_item(({"tapestry","tapestries"}),BSN("These look like really "+
    "ancient tapestries, judging by both texture and images depicted. "+
    "You see some Numenorean warlord, stepping ashore "+
    "on some sandy beach, being met by dark-skinned men wearing "+
    "little clothing. Along the edge of the tapestries, text "+
    "has been embroidered."));
  add_item("text",BSN("The text explains that the tapestry depicts "+
    "the founding of Umbar, a city in Harad in the South."));
  add_item("stairs",BSN("White stone steps lead down to the ground floor "+
    "below."));
  add_prop(ROOM_I_INSIDE,1);
  add_exit(HOH_DIR + "ne_upcorr","west",0,0);
  add_exit(HOH_DIR + "e_upcorr","south",0,0);
  add_exit(HOH_DIR + "ne_stair","down",0,1);
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

