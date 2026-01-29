/*
 *  /d/Gondor/guilds/rangers/obj/n_c_door1.c
 *
 *  outer door to North Headquarters council room.
 *
 *  Coded by Elessar
 *    Modified by Alto, 15 July 2001, to meet new rangers theme.
 *
 */
inherit "/std/door";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

public void
create_door()
{
    set_door_id("north_council_door");
    set_pass_command(({"s","south"}));
    set_door_name(({"wooden door","door"}));
    set_other_room(RANGERS_NOR_DIR + "north_council");
    set_door_desc("The door is made of solid oak. 'The Council of Rangers' " +
        "is written on it in big letters.\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_knock_command("knock");
    set_key("Council_Key");
}


int
open_door(string arg)
{
  if (query_locked())
  {
    if (!(unlock_door(arg + " with gold key")))
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

  write("After you close the door, you decide to lock it as well.\n");
  return (lock_door(arg + " with gold key"));
}
