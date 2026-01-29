/*
 *  /d/Gondor/minas/obj/king_door_in.c
 *
 *  Door of the House of Kings
 *
 *  Last modified by Alto, 20 May 2001
 *
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
  set_door_id("king_door");
  set_pass_command(({"n","north"}));
  set_door_name(({"door"}));
  set_other_room(INNER_MINAS + "/houses/kings6");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_door_desc("Before you is a strong door made of stone.\n");
  set_open(1);
  set_locked(0);
  set_key("Key_To_King_Door");
}
