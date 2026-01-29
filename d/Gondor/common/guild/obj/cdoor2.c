#pragma save_binary
#pragma strict_types

inherit "/std/door";

#include "/d/Gondor/defs.h"

public void
create_door()
{
  ::create_door();
  set_door_id("councildoor");
  set_pass_command(({"e","east"}));
  set_door_name(({"wooden door","door"}));
  set_other_room(RANGER_GON_DIR + "office");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
  set_locked(1);
  set_key("council_key");
  set_knock_command("knock");
}

int
open_door(string arg)
{
  if (query_locked())
  {
    if (!(unlock_door(arg + " with _council_key")))
    {
      return 0;
    }
    write("You decide to unlock the door before opening it.\n");
  }

  return (::open_door(arg));
}

int
close_door(string arg)
{
  if (!(::close_door(arg)))
  {
    return 0;
  }

  write("After you close the door you decide to lock it as well.\n");
  return (lock_door(arg + " with _council_key"));
}
