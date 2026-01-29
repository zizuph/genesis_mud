inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#define TRUSTED_IN_HOH   "_trusted_in_houses_of_healing"

create_room()
{
  set_short("The east corner of the ground floor");
  set_long(BSN("You are at the east end of the long corridor on "+
    "the ground floor. An archway to the south leads to the east wing "+
    "corridor, along which you see a few doors on the left side. "+
    "The foot of a straight stair is further west, it's top steps "+
    "disappearing up through the ceiling above. The smell of "+
    "ointments and herbs lingers in the air, mixed with a musty "+
    "scent, probably emanating from the tapestries decorating the "+
    "white stone walls."));
  add_item(({"window","garden","windows"}),BSN(
    "Outside you see a green garden before the Houses of Healing."));
  add_item(({"tapestry","tapestries"}),BSN("These seemingly ancient "+
    "tapestries of some kind of woven linen, seem to depict the "+
    "Hallow upon the heights of Meneltarma in Numenor, where the "+
    "Faithful Numenoreans offered the first fruits each year "+
    "to Eru Illuvatar, the One."));
  add_item("corridor",BSN("You are standing at the end of the "+
    "white-walled corridor of the main building of the House. "+
    "Going west will take you towards the main entrance hall. "+
    "Another corridor starts beyond the south archway."));
  add_item(({"archway","ornaments"}),BSN("Beautifully carved ornaments adorn the "+
    "stone archway in the south wall. Beyond you see another stone-"+
    "walled corridor and a few doors."));
  add_item(({"stairs","stair","steps"}),BSN("The foot of the stair "+
    "is to the west of here, and the stair leads up to the first "+
    "floor of the Houses of Healing."));
    add_prop(ROOM_I_INSIDE,1);
  add_exit(HOH_DIR + "ne_stair","west",0,0);
  add_exit(HOH_DIR + "e_corr","south",0,0);
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

