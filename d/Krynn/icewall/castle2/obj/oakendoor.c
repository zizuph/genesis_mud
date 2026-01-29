#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/castle2/local.h"
inherit "/std/door";

void
create_door()
{
  set_pass_command(({"e", "east"}));
  set_door_id("sturdy oaken door");
  set_name(({"sturdy oaken door","oaken door","sturdy door","door"}));
  set_door_name(({"sturdy oaken door","oaken door","sturdy door","door"}));
  set_door_desc("sturdy oaken door");
  set_long("This sturdy, but otherwise plain door leads east, " +
    "out of the grand hall.\n");
  set_open_desc("An open sturdy oaken door leading east.\n");
  set_closed_desc("A closed sturdy oaken door.\n");

  set_other_room(ROOMSK + "library");
  set_open(0);
 
}
