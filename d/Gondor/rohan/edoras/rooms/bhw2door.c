inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
  ::create_door();
  set_door_id("barracks_office2");
  set_pass_command(({"w","west"}));
  set_door_name(({"wooden door","door"}));
  set_other_room(EDORAS_DIR + "rooms/boffice2");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
  set_open_desc(0);
  set_closed_desc(0);
  set_locked(0);
  set_key("_elfhelms_office_key");
}
