inherit "/std/door";
#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>

create_door()
{
   ::create_door();
   
   set_door_id("5_door");
   set_pass_command(({"d", "down"}));
   set_door_name(({"wooden door", "door"}));
   set_other_room(LB_SMIAL_DIR + "5_cellar");
//   set_lock_command("lock");
//   set_lock_name("lock");
//   set_lock_desc("It's a small lock made of metal and looks well used.\n");
//   set_unlock_command("unlock");
   set_open(0);
   set_locked(0);

set_pick(15 + random(5));
}
