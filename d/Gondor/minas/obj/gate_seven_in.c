/*
 *  /d/Gondor/minas/obj/gate_seven_in.c
 *
 *  Gate to the Seventh Circle
 *
 *  Last modified by Alto, 28 April 2001
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
  set_door_id("gate_seven_door");
  set_pass_command(({"e","east"}));
  set_door_name(({"seventh gate", "gate", "gates"}));
  set_other_room(INNER_MINAS + "/gate7");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_door_desc("The two doors look "
        + "well-made and very strong. During the day, those "
        + "involved in the business of the Steward must pass through "
        + "them to enter or exit the Citadel. At night, however, the "
        + "Tower Guard do not permit passage.\n");
  set_open(0);
  set_locked(1);
  set_key("Key_To_Seventh_Gate");
}
