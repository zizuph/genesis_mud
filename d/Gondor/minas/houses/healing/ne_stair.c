inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#define TRUSTED_IN_HOH   "_trusted_in_houses_of_healing"

create_room()
{
  set_short("The stairway in the east wing of the Houses of Healing");
  set_long(BSN("White stone walls form a long corridor here, which "+
    "seems to lead to a large hall to the west. A straight stair, also "+
    "made of stone, climbs to the first floor from here, filling half "+
    "of the wide corridor. Beyond the stairway to the east you notice "+
    "the corridor turns around a corner. A glass window is open in the "+
    "south wall, letting some fresh air into the strange-scented corridor."));
  add_item(({"window","garden","windows"}),BSN(
    "Outside you see a green garden behind the Houses of Healing."));
  add_item("hall","That may be the main entrance hall.\n");
  add_item(({"stair","steps","stairway"}),BSN(
    "Smooth white stone steps form a straight stair leading up "+
    "to the first floor of the Houses of Healing. The stairway "+
    "claims almost half of the width of the white-walled corridor, "+
    "as it climbs east up to the end of a similar corridor above."));
  add_item(({"corridor","wall","walls"}),BSN("White and smooth stone walls have been "+
    "expertly constructed many centuries ago, and will most likely "+
    "for at least as long a time still form this corridor. You see "+
    "a great hall at the corridors west end, while there seems "+
    "to be a corner in the east direction. Stairs lead up to a "+
    "seemingly similar corridor on the floor above."));
   add_prop(ROOM_I_INSIDE,1);
  add_exit(HOH_DIR + "main_entr","west",0,0);
  add_exit(HOH_DIR + "ne_corr","east",0,0);
  add_exit(HOH_DIR + "ne_upstair","up",0,2);
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

