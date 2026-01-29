#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/castle2/local.h"
inherit "/std/door";

void
create_door()
{
  set_pass_command(({"w", "west"}));
  set_name(({"sturdy oaken door","oaken door","sturdy door","door"}));
  set_door_name(({"sturdy oaken door","oaken door","sturdy door","door"}));
  set_door_desc("sturdy oaken door");
  set_long("This sturdy, but otherwise plain door leads out of the " +
    "library and into the grand hall.\n");
  set_open_desc("An open sturdy oaken door leading west.\n");
  set_closed_desc("A closed sturdy oaken door.\n");
  set_door_id("sturdy oaken door");
  set_other_room(ROOMSK + "hall1");
  set_open(0);
 
}
