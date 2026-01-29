/*
 *  /d/Gondor/minas/obj/tower_door_in.c
 *
 *  Door of the White Tower of Ecthelion
 *
 *  Last modified by Alto, 20 April 2001
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
  set_door_id("white_tower_door");
  set_pass_command(({"e","east"}));
  set_door_name(({"door"}));
  set_other_room(INNER_MINAS + "/citadel/tower_entrance");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_door_desc("Two massive doors made of wood "
        + "banded in great plates of iron. These doors have never been "
        + "broken, and gazing upon their might you wonder at the "
        + "kind of strength that would be required to even scratch "
        + "the huge timbers.\n");
  set_open(0);
  set_locked(1);
  set_key("Key_To_Tower_Door");
}
