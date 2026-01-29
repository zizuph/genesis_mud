inherit "/std/door";
#include "/d/Gondor/defs.h"
#include <macros.h>

create_door()
{
  ::create_door();
  set_door_id("barracks_office2");
  set_pass_command(({"e","east"}));
  set_door_name(({"wooden door","door"}));
  set_other_room(EDORAS_DIR + "rooms/bhallway");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
  set_locked(0);
  set_key("_elfhelms_office_key");
  set_open_desc(0);
  set_closed_desc(0);
}

int
pass_door(string arg)
{
    object attacker = TP->query_attack();
    if (objectp(attacker) &&
        attacker->id("_Rohirrim_guard") && random(9))
    {
        TP->catch_msg(QCTNAME(attacker) + " blocks your way out the door!\n");
	TP->add_fatigue(-2);
        return 1;
    }
    else
        return ::pass_door(arg);
}

