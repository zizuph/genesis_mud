/*
 *  /d/Gondor/minas/obj/throne_door_stair.c
 *
 *  Door to the stairwell of the White Tower of Ecthelion
 *
 *  Last modified by Alto, 20 April 2001
 *  Serif, April 21, 2002: updated key.
 */

#pragma strict_types

inherit "/std/door";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define INNER_MINAS "/d/Gondor/minas"

public void
create_door()
{
  ::create_door();
  set_door_id("white_tower_stair");
  set_pass_command(({"s","south"}));
  set_door_name(({"stone door"}));
  set_door_name(({"door"}));
  set_other_room(INNER_MINAS + "/citadel/tower3");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_door_desc("This is a rather plain door made of white stone. It "
        + "is obvious only because it is relatively unadorned in a hall "
        + "of such ornate elegance.\n");
  set_open(0);
  set_locked(1);
  set_key("New_Key_To_Tower_Stair");
}
