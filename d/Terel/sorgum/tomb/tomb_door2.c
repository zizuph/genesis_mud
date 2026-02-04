inherit "/std/door";

#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"
#include "tomb.h"

create_door()
{
     ::create_door();
     set_door_id("tomb_door");
     set_pass_command(({"s", "south", "enter", "in"}));
     set_door_desc(BSN(
		   "A ponderous and forebodding slab of stone hanging " +
		   "on rusty iron hinges\n"
		  ));
     set_closed_desc("The door will have to be opened more to permit egress.\n");
     set_open_desc("The opening looks big enough to permit egress.\n");
     set_door_name(({"stone door", "stone slab", "door", "slab"}));
     set_other_room(TOMBDIR + "tomb_ent");

     set_lock_command("lock");
     set_lock_name(({"lock", "padlock"}));
     set_lock_desc(BSN("The lock is on the other side of the door!\n"));

     set_unlock_command("unlock");
	  
     set_open(0);
     set_locked(0);
}

