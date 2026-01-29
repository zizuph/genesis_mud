inherit "/std/door";

#include "/d/Gondor/defs.h"

void
create_door()
{
    set_other_room(ITH_DIR + "emyn-arnen/palace/cellar");
    set_door_id("Emyn-Arnen_Treasury_Gate");
    set_door_name(({"steel gate", "heavy gate", "magic gate", "gate"}));
    set_door_desc(BSN(
        "The heavy steel gate is leading north out of the treasury. "
      + "It has no visible lock, and from this side all one can "
      + "see is a plain unadorned steel plate."));

    set_pass_command("north");

    set_open(0);

    set_str(40);
}
