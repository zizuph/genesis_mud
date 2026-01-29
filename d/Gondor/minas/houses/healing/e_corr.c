inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#define TRUSTED_IN_HOH   "_trusted_in_houses_of_healing"

create_room()
{
  set_short("The corridors in the east wing of the Houses of Healing");
  set_long(BSN("This is the east wing corridor of the House, "+
    "shaped with white stone walls as the rest, and a few doors "+
    "and doorways to chambers of healing and recuperation. An "+
    "archway is in the north end of the corridor, opening out to "+
    "another corridor, in the main building of the House. A large "+
    "tapestry decorates the end wall of this long hallway."));
  add_item(({"window","garden","windows"}),BSN(
    "Outside you see a green garden behind the Houses of Healing."));
  add_item(({"tapestry","tapestries"}),BSN("The musty tapestries "+
    "decorating the south end of the corridor depict ancient times "+
    "of the history of Middle-earth; the first meeting "+
    "of Beren son of Barahir, and Luthien Tinuviel, the elven maid "+
    "and daughter of Thingol and Melian, in the glades near Esgalduin."));
    add_prop(ROOM_I_INSIDE,1);
  add_exit(HOH_DIR + "ne_corr","north",0,0);
  clone_object(HOH_DIR + "doors/hr2outdoor")->move(TO);
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

